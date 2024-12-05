#include "World.h"
#include "Chunk.h"
#include "Block.h"
#include "Texture.h"
#include "Game.h"
#include "Chicken.h"
#include "Fox.h"
#include "Wolf.h"

// 创建世界
World::World()
{
	chunks.clear();
	future_chunks_pos.clear();
	mobs.clear();
	seed = 0;
}

// 从另一个世界创建
World::World(const World& other)
{
	*this = other;
}

// 销毁世界
World::~World()
{
	for (auto& chunk : chunks)
		delete chunk;

	for (auto& mob : mobs)
		delete mob;
}

// 赋值运算符重载
World& World::operator=(const World& other)
{
	chunks = other.chunks;
	future_chunks_pos = other.future_chunks_pos;
	mobs = other.mobs;
	seed = other.seed;

	return *this;
}

// 根据给定位置查找方块
Block& World::operator[](const glm::ivec3& block_pos) const
{
	// 检查位置是否有效
	if (block_pos.y < 0 || block_pos.y >= Chunk::height)
		return Block::air;

	// 查找包含该方块的区块
	Chunk* chunk = find_chunk(block_to_chunk(block_pos));

	// 如果没有找到对应的区块，说明位置无效
	if (chunk == NULL)
		return Block::air;

	// 请求区块中的方块
	return (*chunk)[block_pos];
}

// 加载一个区块
void World::add_chunk(const glm::ivec3& chunk_pos)
{
	// 创建并添加区块
	lock.lock();
	chunks.push_back(new Chunk(chunk_pos, this));
	lock.unlock();

	// 删除该位置的未来区块

	auto it = std::find(future_chunks_pos.begin(), future_chunks_pos.end(), chunk_pos);

	if (it != future_chunks_pos.end())
		future_chunks_pos.erase(it);

	// 更新周围每个区块的世界
	for (uint8_t i = 0; i < around_positions.size(); i++)
	{
		glm::ivec3 pos = chunks.back()->position + (around_positions[i] * (int)Chunk::size);
		Chunk* chunk = find_chunk(pos);

		// 为新创建的区块周围添加未来的区块
		if (chunk == NULL && std::count(future_chunks_pos.begin(), future_chunks_pos.end(), pos) == 0)
			future_chunks_pos.push_back(pos);

		if (chunk != NULL)
		{
			// 更新新创建区块与周围区块之间的链接
			chunks.back()->chunks_around.push_back(chunk);
			chunk->chunks_around.push_back(chunks.back());

			// 更新新创建区块和周围区块的高度限制

			if (chunks.back()->layer_min > chunk->local_layer_min)
				chunks.back()->layer_min = chunk->local_layer_min;

			if (chunks.back()->layer_max < chunk->local_layer_max)
				chunks.back()->layer_max = chunk->local_layer_max;

			if (chunk->layer_min > chunks.back()->local_layer_min)
				chunk->layer_min = chunks.back()->local_layer_min;

			if (chunk->layer_max < chunks.back()->local_layer_max)
				chunk->layer_max = chunks.back()->local_layer_max;
		}
	}

	// 更新新创建的区块
	chunks.back()->update_all();

	// 更新周围区块的边界
	for (auto chunk_around : chunks.back()->chunks_around)
		if (chunk_around != NULL)
			chunk_around->update_edges();
}

// 删除一个区块
void World::remove_chunk(Chunk* chunk)
{
	lock.lock();
	auto chunk_pos = chunk->position;
	auto chunks_around = chunk->chunks_around;

	// 删除周围的未来区块
	for (auto around : around_positions)
	{
		glm::ivec3 pos = chunk_pos + (around * (int)Chunk::size);
		auto future_chunk_pos = std::find(future_chunks_pos.begin(), future_chunks_pos.end(), pos);

		if (future_chunk_pos != future_chunks_pos.end() && nb_chunks_around(*future_chunk_pos) <= 1)
			future_chunks_pos.erase(future_chunk_pos);
	}

	// 删除指向已删除区块的指针
	for (auto c : chunks_around)
		if (c != NULL)
		{
			auto c_chunks_around = c->chunks_around;

			for (auto chunk_around : c_chunks_around)
				if (chunk_around == chunk || chunk_around == NULL)
					c->chunks_around.remove(chunk_around);
		}

	// 移除区块并将其位置添加为未来区块
	future_chunks_pos.push_back(chunk_pos);
	chunks.remove(chunk);
	delete chunk;

	lock.unlock();

	// 更新周围区块的边界
	for (auto chunk_around : chunks_around)
		if (chunk_around != NULL)
			chunk_around->update_edges();
}

// 给定方块位置，返回该方块所在的区块坐标
glm::ivec3 World::block_to_chunk(const glm::ivec3& block_pos) const
{
	glm::ivec3 result = glm::ivec3(0, 0, 0);

	if (block_pos.x >= 0)
		result.x = block_pos.x - (block_pos.x % Chunk::size);

	else
	{
		result.x = -((-block_pos.x) - ((-block_pos.x) % Chunk::size));

		if ((-block_pos.x) % Chunk::size != 0)
			result.x -= Chunk::size;
	}

	if (block_pos.z >= 0)
		result.z = block_pos.z - (block_pos.z % Chunk::size);

	else
	{
		result.z = -((-block_pos.z) - ((-block_pos.z) % Chunk::size));

		if ((-block_pos.z) % Chunk::size != 0)
			result.z -= Chunk::size;
	}

	return result;
}

// 查找给定位置的区块
Chunk* World::find_chunk(const glm::ivec3& chunk_pos) const
{
	for (auto& chunk : chunks)
		if (chunk->position == chunk_pos)
			return chunk;

	return NULL;
}

// 返回给定位置周围的区块数量
uint8_t World::nb_chunks_around(const glm::ivec3& chunk_pos) const
{
	uint8_t i = 0;

	for (auto& chunk : chunks)
	{
		for (auto around : around_positions)
			if (chunk->position == chunk_pos + (around * (int)Chunk::size))
				i++;

		if (i == 4)
			break;
	}

	return i;
}

// 给定玩家与区块的距离
float World::get_distance(const glm::vec3& player_pos, const glm::ivec3& chunk_pos) const
{
	return sqrt(pow(player_pos.x - chunk_pos.x, 2) + pow(player_pos.z - chunk_pos.z, 2));
}

// 给玩家选择的方块
Block* World::get_selected_block(const Player& player)
{
	return NULL;
}

// 给玩家位置添加一个区块
void World::init(const int64_t& seed, const glm::vec3& player_pos)
{
	srand(seed);
	this->seed = rand();

	glm::mat4 water_scale = glm::scale(glm::mat4(1.f), glm::vec3(Chunk::size, Chunk::size, Chunk::size));
	glm::mat4 water_rotation = glm::rotate(glm::mat4(1.f), pi / 2.f, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 water_shift = glm::translate(glm::mat4(1.f), glm::vec3(Chunk::size / 2.f - 0.5f, water_level, Chunk::size / 2.f - 0.5f));

	glm::mat4 limits_scale = glm::scale(glm::mat4(1.f), glm::vec3(Chunk::size, 10000.f, Chunk::size));
	glm::mat4 limits_shift = glm::translate(glm::mat4(1.f), glm::vec3(Chunk::size / 2.f - 0.5f, 0.f, Chunk::size / 2.f - 0.5f));

	Chunk::water_top.send_data(Shader::water, (water_shift * water_rotation * water_scale) * Mesh::square);
	Chunk::water_bottom.send_data(Shader::in_water, (water_shift * water_rotation * water_scale) * Mesh::square);
	Chunk::limits.send_data(Shader::debug, (limits_shift * limits_scale) * Mesh::empty_cube, DataType::Positions);

	add_chunk(block_to_chunk(player_pos));
}

// 生成已加载区块周围的区块
void World::generate(const glm::vec3& player_pos)
{
	bool finish = false;

	// 删除离玩家太远的区块
	for (auto& chunk : chunks)
		if (chunk != NULL && get_distance(player_pos, chunk->position) > Chunk::max_distance * 1.3f)
		{
			remove_chunk(chunk);
			finish = true;
			break;
		}

	// 加载离玩家太近的区块
	if (!finish)
	{
		auto temp = future_chunks_pos;

		for (auto future_chunk_pos : temp)
			if (get_distance(player_pos, future_chunk_pos) < Chunk::max_distance)
				add_chunk(block_to_chunk(future_chunk_pos));
	}

	generate_meshes();
}

// 生成 OpenGL 顶点
void World::generate_meshes()
{
	for (auto& chunk : chunks)
		if (!chunk->as_updated)
			chunk->generate_mesh();
}

// 将顶点发送到着色器
void World::send_meshes()
{
	for (auto& chunk : chunks)
		if (!chunk->as_sent && chunk->as_updated)
			chunk->send_mesh();
}

// 更新世界中的生物
void World::update_mobs(const glm::vec3& player_pos)
{
	// 添加新的生物
	if (mobs.size() < nb_max_mobs && rand_probability(0.1f) && chunks.back()->local_layer_min > water_level)
	{
		// 随机生成一个生物的位置，位置范围相对于玩家位置
		glm::vec3 mob_pos = glm::vec3(
			random_float(player_pos.x - Chunk::max_distance / 2.f, player_pos.x + Chunk::max_distance / 2.f),
			0.f,  // y轴坐标暂时设为0
			random_float(player_pos.x - Chunk::max_distance / 2.f, player_pos.x + Chunk::max_distance / 2.f)
		);

		// 根据生成的位置找到对应的块（chunk）
		Chunk* chunk = find_chunk(block_to_chunk(glm::ivec3(mob_pos)));

		// 如果找到对应的chunk，并且生物距离玩家较近，且该chunk的海拔高于水面
		if (chunk != NULL && glm::distance(glm::vec2(player_pos.x, player_pos.z), glm::vec2(mob_pos.x, mob_pos.z)) < Chunk::max_distance / 2.f && chunk->local_layer_min > water_level)
		{
			// 根据概率生成不同类型的生物
			if (rand_probability(1.f / 3.f))
				mobs.push_back(new Chicken(glm::vec3(mob_pos.x, chunk->local_layer_max + 1, mob_pos.z)));  // 生成鸡

			else if (rand_probability(1.f / 3.f))
				mobs.push_back(new Fox(glm::vec3(mob_pos.x, chunk->local_layer_max + 1, mob_pos.z)));  // 生成狐狸

			else
				mobs.push_back(new Wolf(glm::vec3(mob_pos.x, chunk->local_layer_max + 1, mob_pos.z)));  // 生成狼
		}
	}

	// 更新所有生物的状态
	for (auto& mob : mobs)
		mob->update(*this, player_pos);

	// 删除距离玩家太远或者应该消失的生物
	for (auto it = mobs.begin(); it != mobs.end();)
	{
		if ((*it)->will_dispawn)  // 如果生物的will_dispawn为true，表示它应该消失
		{
			delete* it;  // 删除该生物
			it = mobs.erase(it);  // 从生物列表中移除该生物，并更新迭代器指向下一个元素
		}
		else
		{
			++it;  // 如果没有删除，继续遍历下一个生物
		}
	}
}

// 显示方块
void World::draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane) const
{
	Shader::block.bind();
	Texture::blocks.bind(0);

	for (auto& chunk : chunks)
		if (chunk->is_visible(camera))
			chunk->draw(camera, lights, clipping_plane);

	Texture::unbind();
	Shader::unbind();
}

// 显示水面
void World::draw_water(const Camera& camera, const std::vector<const Light*>& lights) const
{
	glDisable(GL_CULL_FACE);

	if (Game::in_water)
		Shader::in_water.bind();

	else
		Shader::water.bind();

	VertexBuffer& water = Game::in_water ? Chunk::water_bottom : Chunk::water_top;

	Texture::water_dudv.bind(2);
	Texture::water_normals.bind(3);
	water.bind();

	water.send_uniform("u_time", Game::time);
	water.send_uniform("u_camera", camera.get_position());
	water.send_uniform("u_water_level", water_level);
	water.send_uniform("u_color", Material::water.get_color());
	water.send_uniform("u_ambient", Material::water.get_ambient());
	water.send_uniform("u_diffuse", Material::water.get_diffuse());
	water.send_uniform("u_specular", Material::water.get_specular());
	water.send_uniform("u_shininess", Material::water.get_shininess());

	if (!Game::in_water)
		water.send_texture("u_reflection", 0);

	water.send_texture("u_refraction", 1);
	water.send_texture("u_water_dudv", 2);
	water.send_texture("u_water_normals", 3);

	std::vector<int> light_types;
	std::vector<glm::vec3> light_vectors;
	std::vector<ColorRGB> light_colors;
	std::vector<float> light_intensities;

	for (uint16_t i = 0; i < std::min((int)lights.size(), (int)nb_max_lights); i++)
	{
		light_types.push_back((int)lights[i]->get_type());
		light_vectors.push_back(lights[i]->get_vector());
		light_colors.push_back(ColorRGB(lights[i]->get_color()));
		light_intensities.push_back(lights[i]->get_intensity());
	}

	water.send_uniform("u_light_types", light_types);
	water.send_uniform("u_light_vectors", light_vectors);
	water.send_uniform("u_light_colors", light_colors);
	water.send_uniform("u_light_intensities", light_intensities);
	water.send_uniform("u_nb_lights", std::min((int)lights.size(), (int)nb_max_lights));

	for (auto& chunk : chunks)
		if (chunk->is_visible(camera))
			chunk->draw_water(camera, lights);

	VertexBuffer::unbind();
	Texture::unbind();
	Texture::unbind();
	Shader::unbind();
	glEnable(GL_CULL_FACE);
}

// 显示生物
void World::draw_mobs(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane) const
{
	for (auto& mob : mobs)
		mob->draw(camera, lights, clipping_plane);
}

// 显示调试信息
void World::draw_debug(const Camera& camera) const
{
	glDisable(GL_CULL_FACE);
	Shader::debug.bind();
	Chunk::limits.bind();

	for (auto chunk : chunks)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(chunk->position));
		Chunk::limits.send_uniform("u_mvp", camera.get_matrix() * model);

		Chunk::limits.draw(DrawType::Lines);
	}

	VertexBuffer::unbind();
	Shader::unbind();
	glEnable(GL_CULL_FACE);
}

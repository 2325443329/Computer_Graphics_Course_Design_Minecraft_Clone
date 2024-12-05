#include "Player.h"

// 创建一个玩家

Player::Player()
{
	previous_pos = glm::vec3();
	position = glm::vec3();
	hitbox.fill(glm::vec3());
	speed = glm::vec3();;
	in_air = false;
	chunk = NULL;
	fly = false;
	first_person = false;
}

// 从另一个玩家创建一个玩家
Player::Player(const Player& other)
{
	*this = other;
}

// 从玩家的位置创建一个玩家
Player::Player(const glm::vec3& position)
{
	skin = Skin(glm::vec3(0.f, 0.f, 0.f), glm::vec3());

	speed = glm::vec3(0.f, 0.f, 0.f);
	in_air = true;

	hitbox =
	{
		glm::vec3(-0.5f + epsilon, -1.f + epsilon, -0.5f + epsilon), glm::vec3(-0.5f + epsilon, -1.f + epsilon, 0.5f - epsilon),
		glm::vec3(0.5f - epsilon, -1.f + epsilon, -0.5f + epsilon), glm::vec3(0.5f - epsilon, -1.f + epsilon, 0.5f - epsilon),
		glm::vec3(-0.5f + epsilon,  0.f          , -0.5f + epsilon), glm::vec3(-0.5f + epsilon,  0.f          , 0.5f - epsilon),
		glm::vec3(0.5f - epsilon,  0.f          , -0.5f + epsilon), glm::vec3(0.5f - epsilon,  0.f          , 0.5f - epsilon),
		glm::vec3(-0.5f + epsilon,  1.f - epsilon, -0.5f + epsilon), glm::vec3(-0.5f + epsilon,  1.f - epsilon, 0.5f - epsilon),
		glm::vec3(0.5f - epsilon,  1.f - epsilon, -0.5f + epsilon), glm::vec3(0.5f - epsilon,	 1.f - epsilon, 0.5f - epsilon)
	};

	chunk = NULL;
	fly = false;


	previous_pos = position;
	this->position = position;

	first_person = true;

	skin.move(this->position);
	camera.set_position((skin.body.propagated_matrix * skin.neck.propagated_matrix * skin.head.propagated_matrix * skin.camera.propagated_matrix) * glm::vec3(0.f, 0.f, 0.f));
}


// 赋值操作符重载
Player& Player::operator=(const Player& other)
{
	skin = other.skin;
	camera = other.camera;
	previous_pos = other.previous_pos;
	position = other.position;
	hitbox = other.hitbox;
	speed = other.speed;
	in_air = other.in_air;
	chunk = other.chunk;
	fly = other.fly;
	first_person = other.first_person;

	return *this;
}

// 获取玩家位置
glm::vec3 Player::get_position() const
{
	return position;
}

// 根据鼠标的移动来改变摄像机的方向
void Player::look(const glm::ivec2& mouse_pos)
{
	camera.look(mouse_pos);
}

// 根据鼠标的移动来改变头部的方向
void Player::update_head()
{
	skin.rotate_head(camera.get_yaw(), camera.get_pitch());
	camera.set_position((skin.body.propagated_matrix * skin.neck.propagated_matrix * skin.head.propagated_matrix * skin.camera.propagated_matrix) * glm::vec3(0.f, 0.f, 0.f));
}

// 移动操作
void Player::move(const Uint8* keystates, World& world)
{
	previous_pos = position;
	float move_speed = (keystates[SDL_SCANCODE_LSHIFT] ? run_speed : walk_speed);
	skin.walking = false;
	skin.running = false;
	skin.forward = false;
	skin.left = false;
	skin.right = false;
	skin.back = false;

	if (keystates[SDL_SCANCODE_A])
	{
		skin.walking = true;
		skin.left = true;
	}

	if (keystates[SDL_SCANCODE_D])
	{
		skin.walking = true;
		skin.right = true;
	}

	if (keystates[SDL_SCANCODE_W])
	{
		skin.walking = true;
		skin.forward = true;
	}

	if (keystates[SDL_SCANCODE_S])
	{
		skin.walking = true;
		skin.back = true;
	}

	if (fly)
	{
		if (keystates[SDL_SCANCODE_A])
			position -= glm::normalize(glm::cross(camera.get_direction(), glm::vec3(0.f, 1.f, 0.f))) * fly_speed * frame_duration;

		if (keystates[SDL_SCANCODE_D])
			position += glm::normalize(glm::cross(camera.get_direction(), glm::vec3(0.f, 1.f, 0.f))) * fly_speed * frame_duration;

		if (keystates[SDL_SCANCODE_W])
			position += glm::normalize(glm::vec3(camera.get_direction().x, 0.f, camera.get_direction().z)) * fly_speed * frame_duration;

		if (keystates[SDL_SCANCODE_S])
			position -= glm::normalize(glm::vec3(camera.get_direction().x, 0.f, camera.get_direction().z)) * fly_speed * frame_duration;

		if (keystates[SDL_SCANCODE_SPACE])
			position += glm::vec3(0.f, 1.f, 0.f) * fly_speed * frame_duration;

		if (keystates[SDL_SCANCODE_LCTRL])
			position -= glm::vec3(0.f, 1.f, 0.f) * fly_speed * frame_duration;

		find_player_chunk(world);
		in_air = true;
		speed = glm::vec3(0.f, 0.f, 0.f);
	}

	else
	{
		skin.running = keystates[SDL_SCANCODE_LSHIFT];

		if (position.y <= water_level + 1.f && in_air)
		{
			if (keystates[SDL_SCANCODE_A])
				speed -= glm::normalize(glm::cross(camera.get_direction(), glm::vec3(0.f, 1.f, 0.f))) * walk_speed * frame_duration;

			if (keystates[SDL_SCANCODE_D])
				speed += glm::normalize(glm::cross(camera.get_direction(), glm::vec3(0.f, 1.f, 0.f))) * walk_speed * frame_duration;

			if (keystates[SDL_SCANCODE_W])
				speed += glm::normalize(glm::vec3(camera.get_direction().x, 0.f, camera.get_direction().z)) * walk_speed * frame_duration;

			if (keystates[SDL_SCANCODE_S])
				speed -= glm::normalize(glm::vec3(camera.get_direction().x, 0.f, camera.get_direction().z)) * walk_speed * frame_duration;

			if (keystates[SDL_SCANCODE_SPACE])
				speed += glm::vec3(0.f, 1.f, 0.f) * run_speed * frame_duration;

			if (keystates[SDL_SCANCODE_LCTRL])
				speed -= glm::vec3(0.f, 1.f, 0.f) * run_speed * frame_duration;

			in_air = true;
		}

		else if (in_air)
		{
			if (keystates[SDL_SCANCODE_A])
				speed -= glm::normalize(glm::cross(camera.get_direction(), glm::vec3(0.f, 1.f, 0.f))) * move_speed * 2.f * frame_duration;

			if (keystates[SDL_SCANCODE_D])
				speed += glm::normalize(glm::cross(camera.get_direction(), glm::vec3(0.f, 1.f, 0.f))) * move_speed * 2.f * frame_duration;

			if (keystates[SDL_SCANCODE_W])
				speed += glm::normalize(glm::vec3(camera.get_direction().x, 0.f, camera.get_direction().z)) * move_speed * 2.f * frame_duration;

			if (keystates[SDL_SCANCODE_S])
				speed -= glm::normalize(glm::vec3(camera.get_direction().x, 0.f, camera.get_direction().z)) * move_speed * 2.f * frame_duration;

			if (get_horizontal_norm(speed) > move_speed)
				set_horizontal_norm(speed, move_speed);
		}

		else
		{
			if (keystates[SDL_SCANCODE_A])
				position -= glm::normalize(glm::cross(camera.get_direction(), glm::vec3(0.f, 1.f, 0.f))) * move_speed * frame_duration;

			if (keystates[SDL_SCANCODE_D])
				position += glm::normalize(glm::cross(camera.get_direction(), glm::vec3(0.f, 1.f, 0.f))) * move_speed * frame_duration;

			if (keystates[SDL_SCANCODE_W])
				position += glm::normalize(glm::vec3(camera.get_direction().x, 0.f, camera.get_direction().z)) * move_speed * frame_duration;

			if (keystates[SDL_SCANCODE_S])
				position -= glm::normalize(glm::vec3(camera.get_direction().x, 0.f, camera.get_direction().z)) * move_speed * frame_duration;

			if (keystates[SDL_SCANCODE_SPACE])
				jump();
		}

		update_position();

		if (previous_pos != position)
			check_hitbox(world);
	}

	if (first_person)
		skin.camera.propagated_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -4.f / 16.f - epsilon));

	else
		skin.camera.propagated_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 5.f));

	skin.move(position);
	camera.set_position((skin.body.propagated_matrix * skin.neck.propagated_matrix * skin.head.propagated_matrix * skin.camera.propagated_matrix) * glm::vec3(0.f, 0.f, 0.f));
}

// 跳跃
void Player::jump()
{
	if (position.y > water_level - 0.5f)
		speed.y = jump_speed;

	in_air = true;
}

// 更新位置
void Player::update_position()
{
	if (!in_air)
	{
		speed = glm::vec3(0.f, 0.f, 0.f);
		return;
	}

	if (position.y > water_level + 1.f)
		speed.y -= gravity * frame_duration;

	else if (position.y > water_level)
		speed.y -= 0.5f * gravity * frame_duration;

	else
	{
		speed.y -= 0.02f * gravity * frame_duration;
		speed *= 0.99f;
	}

	position += speed * frame_duration;
}

// 更新玩家所在的区块
void Player::find_player_chunk(World& world)
{
	if (chunk == NULL)
	{
		chunk = world.find_chunk(world.block_to_chunk(round(position)));
		return;
	}

	if (chunk->position == world.block_to_chunk(round(position)))
		return;

	for (auto c : chunk->chunks_around)
		if (c != NULL && c->position == world.block_to_chunk(round(position)))
		{
			chunk = c;
			return;
		}

	for (auto chunks_around : chunk->chunks_around)
		if (chunks_around != NULL)
			for (auto c : chunks_around->chunks_around)
				if (c != NULL && c->position == world.block_to_chunk(round(position)))
				{
					chunk = c;
					return;
				}
}

// 考虑碰撞
void Player::check_hitbox(World& world)
{
	find_player_chunk(world);

	in_air = true;
	speed = (position - previous_pos) / frame_duration;
	glm::vec3 pos_temp = position;
	std::array<float, 4> x_sign = { 1.f, 1.f, -1.f, -1.f };
	std::array<float, 4> z_sign = { 1.f, -1.f, 1.f, -1.f };

	for (uint8_t i = 0; i < hitbox.size(); i++)
		if ((*chunk)[round(position + hitbox[i])].get_type() != Block::Type::Air && !(*chunk)[round(position + hitbox[i])].is_plant())
		{
			float dist_x = abs((position + hitbox[i]).x - ((*chunk)[round(position + hitbox[i])].get_position().x + x_sign[i % 4] * 0.5f));
			float dist_y = FLT_MAX;
			float dist_z = abs((position + hitbox[i]).z - ((*chunk)[round(position + hitbox[i])].get_position().z + z_sign[i % 4] * 0.5f));

			if (i < 4)
				dist_y = abs((position + hitbox[i]).y - ((*chunk)[round(position + hitbox[i])].get_position().y + 0.5f));

			if (dist_y < dist_x && dist_y < dist_z)
			{
				pos_temp.y = (*chunk)[round(position + hitbox[i])].get_position().y + 0.5f + epsilon_2 - hitbox[i].y;
				speed = glm::vec3(0.f, 0.f, 0.f);
				in_air = false;
			}

			else if (dist_x < dist_z)
			{
				pos_temp.x = (*chunk)[round(position + hitbox[i])].get_position().x + x_sign[i % 4] * (0.5f + epsilon_2) - hitbox[i].x;
				speed.x = 0.f;
			}

			else
			{
				pos_temp.z = (*chunk)[round(position + hitbox[i])].get_position().z + z_sign[i % 4] * (0.5f + epsilon_2) - hitbox[i].z;
				
				// 获取碰撞方块的坐标
				glm::ivec3 collision_block_pos = round(position + hitbox[i]);

				// 检测碰撞方块上方是否有方块
				glm::ivec3 above_block_pos = collision_block_pos + glm::ivec3(0, 0.1, 0);
				if ((*chunk)[above_block_pos].get_type() == Block::Type::Air)
				{
					// 如果上方没有方块，执行跳跃
					jump();
				}
				else
				{
					speed.z = 0.f;
				}
			}
		}

	position = pos_temp;
}

// 如果可以破坏方块，则破坏它
void Player::break_block()
{
	for (float i = 0.f; i < break_distance; i += 0.1f)
	{
		glm::vec3 pos = glm::vec3(0.f, 0.f, -i);

		pos = skin.body.propagated_matrix * skin.neck.propagated_matrix * skin.head.propagated_matrix * pos;

		// std::cout << "Block position: (" 
		// 		<< pos.x << ", " 
		// 		<< pos.y << ", " 
		// 		<< pos.z << ")" << std::endl;
		if ((*chunk->world)[round(pos)].get_type() != Block::Type::Air)
		{
			std::cout << Block::type_to_string((*chunk->world)[round(pos)].get_type()) << std::endl;
			std::cout << "Block position: ("
				<< pos.x << ", "
				<< pos.y << ", "
				<< pos.z << ")" << std::endl;
			(*chunk->world)[round(pos)].set_type(Block::Type::Air, true);
			return;
		}
	}
}

// 放置方块
void Player::place_block()
{
	glm::vec3 last_pos = glm::vec3(0.f, 0.f, 0.f);  // 存储最后一个有效的空气方块位置

	// 根据传入的 block_type 设置相应的方块类型
	Block::Type selected_type;
	switch (block_type)
	{
	case 0: selected_type = Block::Type::Grass; break;  // 选择草方块
	case 1: selected_type = Block::Type::Dirt; break;   // 选择泥土方块
	case 2: selected_type = Block::Type::Stone; break;  // 选择石方块
	case 3: selected_type = Block::Type::Sand; break;   // 选择沙子方块
	case 4: selected_type = Block::Type::Wood; break;   // 选择木块方块
	case 5: selected_type = Block::Type::Leaves; break; // 选择树叶方块
	case 6: selected_type = Block::Type::Snow; break;   // 选择雪方块
	case 7: selected_type = Block::Type::Weed; break;   // 选择杂草方块
	case 8: selected_type = Block::Type::Tulip; break;  // 选择郁金香方块
	case 9: selected_type = Block::Type::Orchid; break; // 选择兰花方块
	case 10: selected_type = Block::Type::Dandelion; break;  // 选择蒲公英方块
	default: selected_type = Block::Type::Air; break;  // 默认类型为 Air
	}


	for (float i = 0.f; i < place_distance; i += 0.1f)
	{
		glm::vec3 pos = glm::vec3(0.f, 0.f, -i);

		// 通过玩家头部的变换矩阵计算实际位置
		pos = skin.body.propagated_matrix * skin.neck.propagated_matrix * skin.head.propagated_matrix * pos;

		// 如果当前位置的方块不是空气
		if ((*chunk->world)[round(pos)].get_type() != Block::Type::Air)
		{
			// 在找到的第一个非空气方块位置处放置新的方块
			std::cout << "当前玩家选择方块为：" << Block::type_to_string(selected_type) << std::endl;
			(*chunk->world)[round(last_pos)].set_type(selected_type, true);
			std::cout << "成功放置方块：" << Block::type_to_string(selected_type) << std::endl;
			return;
		}
		else
		{
			// 如果是空气方块，更新 last_pos
			last_pos = pos;
		}
	}
}


void Player::switch_skin(bool next) {
	skin.switch_skin(next);  // 调用 Skin 类的 switch_skin 方法
}

// 绘制玩家
void Player::draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane) const
{
	skin.draw(camera, lights, clipping_plane);
}

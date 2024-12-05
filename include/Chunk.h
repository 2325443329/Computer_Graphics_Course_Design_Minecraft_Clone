#ifndef CHUNK_H
#define CHUNK_H

#include "utils.h"
#include "Block.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "Mesh.h"

#include <array>

class Player;
class World;
class Game;
class Entity;

// 定义一个块（Chunk）类

class Chunk
{
public:

	static constexpr uint8_t	size = 16;					// 一个块的宽度
	static constexpr uint8_t	height = 128;				// 一个块的高度
	static constexpr uint16_t	max_distance = 5 * size;	// 加载的最大块距离

	typedef std::array<std::array<std::array<Block, size>, height>, size> BlockArray;

	// 尝试实现块边界上的树木功能 :(

	/*
	// 结构体表示待添加的叶子列表

	struct LeavesToAdd
	{
		glm::ivec3					chunk;	// 叶子所在的块位置
		std::vector<glm::ivec3>		leaves;	// 待添加的叶子

									LeavesToAdd();
									LeavesToAdd(const glm::ivec3& chunk_position);
									LeavesToAdd(const LeavesToAdd& other);

		LeavesToAdd&				operator=(const LeavesToAdd& other);
	};
	*/

private:

	World* world;						// 指向世界的指针
	glm::ivec3					position;					// 块的位置
	BlockArray					blocks;						// 块中的方块列表
	uint8_t						local_layer_min;			// 块中的最低层
	uint8_t						local_layer_max;			// 块中的最高层
	uint8_t						layer_min;					// 全局最低层
	uint8_t						layer_max;					// 全局最高层
	bool						as_updated;					// 是否更新了顶点
	bool						as_sent;					// 是否已将顶点发送到着色器
	std::list<Chunk*>			chunks_around;				// 周围的块
	Mesh						mesh;						// 网格
	VertexBuffer				object;						// OpenGL 顶点缓冲区
	bool						as_water;					// 是否包含水

	static VertexBuffer			water_top;					// 水面（上视图）
	static VertexBuffer			water_bottom;				// 水面（下视图）
	static VertexBuffer			limits;						// 块的边界
	//static std::vector<LeavesToAdd>	leaves_to_add;

public:

	Chunk();
	Chunk(const Chunk& other);
	Chunk(const glm::ivec3& position, World* world);

	Chunk& operator=(const Chunk& other);
	Block& operator[](const glm::ivec3& block_pos);

	float						noise(int8_t x, int8_t z, float size, float height, float shift = 0.f);	// 噪声生成
	void						generate_blocks();			// 生成块中的方块
	bool						add_tree(int8_t x, uint8_t y, int8_t z);	// 添加树
	void						add_leave(int8_t x, uint8_t y, int8_t z, bool update_block = false);	// 添加叶子
	void						add_plant(int8_t x, uint8_t y, int8_t z);	// 添加植物
	Block* find_block(const glm::ivec3& block_pos);	// 查找方块
	void						update_all();				// 更新所有块
	void						update_edges();				// 更新块的边缘
	void						update_face(uint8_t face_id);	// 更新指定的面
	void						generate_mesh();				// 生成网格
	void						send_mesh();					// 发送网格数据
	bool						is_visible(const Camera& camera) const;	// 判断块是否可见
	void						draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;	// 绘制块
	void						draw_water(const Camera& camera, const std::vector<const Light*>& lights) const;	// 绘制水面

	friend						World;
	friend						Block;
	friend						Player;
	friend						Entity;
};

#endif

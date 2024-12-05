#ifndef ENTITY_H
#define ENTITY_H

#include "utils.h"
#include "Camera.h"
#include "World.h"
#include "Block.h"
#include "Mesh.h"
#include "VertexBuffer.h"
#include "Texture.h"

// 定义一个实体类
class Entity
{
public:

	static constexpr float		jump_speed = 9.f;	// 跳跃速度
	static constexpr float		walk_speed = 4.5f;	// 行走速度
	static constexpr float		texture_size = 64.f;	// 皮肤的纹理大小

	// 定义模型的一个部件
	class Part
	{
	private:

		VertexBuffer				object;				// OpenGL 顶点缓冲区

	public:

		glm::mat4					propagated_matrix;	// 传播矩阵
		glm::mat4					local_matrix;		// 本地矩阵
		std::vector<Part*>			children;			// 连接的部件

		Part();
		Part(const Part& other);
		Part(Mesh mesh, const glm::vec2& texture_pos, const glm::vec3& size, const std::vector<Part*>& children, bool horizontal);

		Part& operator=(const Part& other);

		void						draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;

		static std::vector<float>	init_texcoords(const glm::vec2& texture_pos, const glm::vec3& size, bool horizontal);
	};

protected:

	float						y_offset;				// 实体的碰撞盒相对于身体的 y 轴偏移
	Part						body;					// 身体
	Part						neck;					// 脖子
	std::array<glm::vec3, 12>	hitbox;					// 实体的碰撞盒	
	glm::vec3					previous_pos;			// 上一位置
	glm::vec3					position;				// 实体的位置	
	glm::vec3					speed;					// 实体的速度	
	bool						in_air;					// 是否在空中
	Chunk* chunk;					// 实体所在的块
	Texture* texture;				// 实体的纹理
	bool						is_blocked;				// 是否与其他物体发生碰撞
	bool						walking;				// 是否正在行走
	glm::mat4					body_initial;			// 身体的初始矩阵
	glm::mat4					neck_initial;			// 脖子的初始矩阵
	float						body_angle;				// 身体的旋转角度
	float						head_angle;				// 头部的旋转角度

public:

	Entity();
	Entity(const Entity& other);
	virtual						~Entity() = 0;

	virtual Entity& operator=(const Entity& other);

	void						move(const glm::vec3& position);	// 移动实体
	void						rotate(float angle);	// 旋转实体
	glm::vec3					get_position() const;	// 获取实体位置
	Chunk* get_chunk() const;		// 获取实体所在的块
	void						jump();					// 让实体跳跃
	void						update_position();		// 更新实体位置
	void						update_rotation();		// 更新实体旋转
	void						find_entity_chunk(const World& world);	// 查找实体所在的块
	void						check_hitbox(const World& world, const glm::vec3& player_pos);	// 检查碰撞盒
	virtual void				update(const World& world, const glm::vec3& player_pos);	// 更新实体
	void						draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;	// 绘制实体
};

#endif

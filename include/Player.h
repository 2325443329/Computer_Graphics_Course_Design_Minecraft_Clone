#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include "Camera.h"
#include "World.h"
#include "Chunk.h"
#include "Block.h"
#include "Skin.h"
#include "Material.h"
#include "Light.h"

// 定义一个玩家类

class Player // : Entity :(
{
public:

	// 常量定义玩家的各种属性
	static constexpr float		jump_speed = 9.f;	// 跳跃速度
	static constexpr float		walk_speed = 7.f;	// 行走速度
	static constexpr float		run_speed = 10.f;	// 跑步速度
	static constexpr float		fly_speed = 25.f;	// 飞行速度
	static constexpr float		break_distance = 10.f;	// 摧毁一个方块的最大距离
	static constexpr float		place_distance = 10.f;	// 放置一个方块的最大距离

private:

	Skin						skin;					// 玩家模型（3D）
	glm::vec3					previous_pos;			// 玩家之前的位置
	glm::vec3					position;				// 玩家当前位置
	std::array<glm::vec3, 12>	hitbox;					// 玩家碰撞箱
	glm::vec3					speed;					// 玩家速度
	bool						in_air;					// 玩家是否在空中
	Chunk* chunk;					// 玩家所在的区块

public:

	Camera						camera;					// 玩家摄像机
	bool						fly;					// 是否启用飞行模式
	bool						first_person;			// 是否为第一人称视角

	int block_type = 0;					// 玩家选择的方块类型

	Player();
	Player(const Player& other);
	Player(const glm::vec3& position);

	Player& operator=(const Player& other);

	// 获取玩家位置
	glm::vec3					get_position() const;

	// 让玩家根据鼠标位置旋转视角
	void						look(const glm::ivec2& mouse_pos);

	// 更新玩家头部的位置
	void						update_head();

	// 让玩家根据键盘输入移动
	void						move(const Uint8* keystates, World& world);

	// 玩家跳跃
	void						jump();

	// 更新玩家的位置信息
	void						update_position();

	// 查找玩家所在的区块
	void						find_player_chunk(World& world);

	// 检查玩家的碰撞箱是否与环境碰撞
	void						check_hitbox(World& world);

	// 玩家摧毁方块
	void						break_block();

	// 玩家放置方块
	void                        place_block();

	// 调用 Skin 的 switch_skin 方法
	void						switch_skin(bool next);

	// 绘制玩家
	void						draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;
};

#endif

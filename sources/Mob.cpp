#include "Mob.h"
#include "Game.h"

// 创建一个怪物

Mob::Mob() : Entity()
{
	time_check = 0;
	tempo = 0;
	time_check_rand = random_int(0, 150) + 50;
	animation_frame = false;
	is_animated = false;
	will_dispawn = false;
}

// 从另一个怪物创建一个3D模型

Mob::Mob(const Mob& other)
{
	*this = other;
}

// 赋值运算符重载

Mob& Mob::operator=(const Mob& other)
{
	Entity::operator=(other);

	time_check = other.time_check;
	tempo = other.tempo;
	time_check_rand = other.time_check_rand;
	animation_frame = other.animation_frame;
	is_animated = other.is_animated;
	will_dispawn = other.will_dispawn;

	return *this;
}

// 控制怪物的行为

void Mob::behaviour()
{
	time_check++;

	if (time_check > time_check_rand)
	{
		if (!walking && time_check < time_check_rand + 2)
			body_angle = random_float(-pi, pi);

		else
		{
			time_check = 0;
			time_check_rand = random_int(0, 80) + 40;
			walking = !walking;
		}
	}

	if (walking)
	{
		if (is_blocked && !in_air)
		{
			if (tempo == 0)
			{
				tempo += 10;
				jump();
			}

			else
				tempo--;
		}

		else
		{
			move(position - glm::vec3(sin(body_angle) * walk_speed * frame_duration, 0.f, cos(body_angle) * walk_speed * frame_duration));
			is_animated = true;
		}
	}

	if (is_animated)
	{
		animation_frame += pi / 32.f;
		animate(animation_frame);

		if (animation_frame >= pi)
		{
			is_animated = false;
			animation_frame = 0;
		}
	}
}

// 更新怪物状态

void Mob::update(const World& world, const glm::vec3& player_pos)
{
	check_hitbox(world, player_pos);
	behaviour();
	update_position();
	update_rotation();
	update_dispawn(player_pos);
}

//// 如果需要则让实体消失(不考虑高度因素)
//void Mob::update_dispawn(const glm::vec3& player_pos)
//{
//    // 如果怪物离玩家太远，设置为会消失
//    if (glm::distance(glm::vec2(player_pos.x, player_pos.z), glm::vec2(position.x, position.z)) > Chunk::max_distance / 2.f)
//        will_dispawn = true;  // 设置 will_dispawn 为 true 表示生物会消失
//}

//  如果需要则让实体消失(考虑高度因素)
void Mob::update_dispawn(const glm::vec3& player_pos)
{
	// 计算生物与玩家之间的三维距离
	float distance = glm::distance(player_pos, position);

	// 如果怪物离玩家太远，设置为会消失
	if (distance > Chunk::max_distance / 2.f)
		will_dispawn = true;  // 设置 will_dispawn 为 true 表示生物会消失
}
// 动画怪物（纯虚函数）

void Mob::animate(float time)
{}

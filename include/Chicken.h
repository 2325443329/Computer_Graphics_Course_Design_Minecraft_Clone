#ifndef CHICKEN_H
#define CHICKEN_H

#include "Mob.h"

// 定义一个鸡类

class Chicken : public Mob
{
private:

	Part		head;					// 头部
	Part		shoulder_1;				// 左肩
	Part		shoulder_2;				// 右肩
	Part		hips_1;					// 左臀
	Part		hips_2;					// 右臀
	Part		leg;					// 腿部
	Part		palm;					// 脚掌
	Part		wing_1;					// 左翼
	Part		wing_2;					// 右翼
	Part		beak;					// 喙
	Part		beak_bottom;			// 喙下部
	Part		wattle;					// 脖肉
	glm::mat4	beak_bottom_initial;	// 喙下部的初始矩阵
	glm::mat4	shoulder_1_initial;		// 左肩的初始矩阵
	glm::mat4	shoulder_2_initial;		// 右肩的初始矩阵
	glm::mat4	hips_1_initial;			// 左臀的初始矩阵
	glm::mat4	hips_2_initial;			// 右臀的初始矩阵

public:

	Chicken();
	Chicken(const Chicken& other);
	Chicken(const glm::vec3& position);

	Chicken& operator=(const Chicken& other);

	void		animate(float time);		// 动画播放，接受时间参数来更新动画状态
};

#endif

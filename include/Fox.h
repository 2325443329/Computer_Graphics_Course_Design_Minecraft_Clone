#ifndef FOX_H
#define FOX_H

#include "Mob.h"

// 定义一个狐狸类

class Fox : public Mob
{
private:

	Part		muzzle;				// 狐狸的嘴巴
	Part		ear_1;				// 左耳
	Part		ear_2;				// 右耳
	Part		head;				// 头部
	Part		tail;				// 尾巴
	Part		leg;				// 腿
	Part		tailbase;			// 尾巴的根部
	Part		shoulder_1;			// 左肩膀
	Part		shoulder_2;			// 右肩膀
	Part		hips_1;				// 左臀部
	Part		hips_2;				// 右臀部
	glm::mat4	shoulder_1_initial;	// 左肩膀的初始矩阵
	glm::mat4	shoulder_2_initial;	// 右肩膀的初始矩阵
	glm::mat4	hips_1_initial;		// 左臀部的初始矩阵
	glm::mat4	hips_2_initial;		// 右臀部的初始矩阵
	glm::mat4	head_initial;		// 头部的初始矩阵
	glm::mat4	tail_initial;		// 尾巴的初始矩阵


public:

	Fox();
	Fox(const Fox& other);
	Fox(const glm::vec3& position);

	Fox& operator=(const Fox& other);

	void		animate(float time);	// 动画更新
};

#endif

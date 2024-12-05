#ifndef SUN_H
#define SUN_H

#include "utils.h"
#include "Luminary.h"

// 定义太阳类，继承自Luminary类

class Sun : public Luminary
{
public:

	// 初始化太阳
	void	init() override;

	// 更新太阳的位置或状态，通常基于玩家的位置
	void	update(const glm::vec3& player_pos) override;
};

#endif

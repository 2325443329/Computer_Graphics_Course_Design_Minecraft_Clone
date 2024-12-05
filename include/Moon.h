#ifndef MOON_H
#define MOON_H

#include "utils.h"
#include "Luminary.h"

// 定义一个月亮类，继承自 Luminary 类

class Moon : public Luminary
{
private:

	bool	inverted; // 月亮的精灵是否反向（表示是否镜像显示）

public:

	// 初始化月亮对象，重写自基类
	void	init() override;

	// 更新月亮的状态，重写自基类
	void	update(const glm::vec3& player_pos) override;
};

#endif

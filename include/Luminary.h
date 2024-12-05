#ifndef LUMINARY_H
#define LUMINARY_H

#include "utils.h"
#include "Light.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "Camera.h"

// 定义天体类

class Luminary
{
protected:

	Texture* texture;				// 天体的纹理
	Light					light;					// 天体的光源
	glm::mat4				model;					// 天体的变换矩阵
	VertexBuffer			object;					// OpenGL的顶点缓冲

	// 静态常量矩阵：缩放、平移和旋转矩阵
	static const glm::mat4	scale_matrix;			// 缩放矩阵
	static const glm::mat4	translation_matrix;		// 平移矩阵
	static const glm::mat4	rotation_matrix;		// 旋转矩阵

public:

	// 天体的常量参数：角度、速度、大小、距离和起始时间
	static constexpr float	angle = pi / 6.f;	// 天体的倾斜角度
	static constexpr float	speed = 0.01f;	// 天体的运动速度
	static constexpr float	size = 30.f;		// 天体的大小
	static constexpr float	distance = 500.f;	// 天体与观察者的距离
	static constexpr float	start_time = pi / 4.f;	// 天体的起始时间

	// 默认构造函数
	Luminary();
	Luminary(const Luminary& other);

	// 赋值运算符
	Luminary& operator=(const Luminary& other);

	// 初始化函数
	virtual void			init();
	// 更新函数，由派生类实现
	virtual void			update(const glm::vec3& player_pos) = 0;
	// 绘制函数
	void					draw(const Camera& camera, const std::vector<const Light*>& lights) const;
	// 获取天体的位置
	glm::vec3				get_position() const;
	// 获取光源
	const Light* get_light() const;
};

#endif

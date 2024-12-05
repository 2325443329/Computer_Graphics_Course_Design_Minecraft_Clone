#ifndef SKY_H
#define SKY_H

#include "utils.h"
#include "Light.h"
#include "Material.h"
#include "Camera.h"
#include "VertexBuffer.h"

// 定义天空类

class Sky
{
private:

	// 天空的颜色属性
	Color					high_color;			// 天空顶部的颜色
	Color					low_color;			// 天空底部的颜色
	Light					light;				// 天空的环境光
	glm::mat4				model;				// 变换矩阵
	VertexBuffer			object;				// OpenGL 顶点缓冲区

	// 静态的缩放矩阵
	static glm::mat4		scale_matrix;		// 缩放矩阵

public:

	// 天空的可视距离常量
	static constexpr float	distance = 550.f;	// 天空的距离

	// 构造函数、拷贝构造函数和赋值操作符
	Sky();
	Sky(const Sky& other);
	Sky& operator=(const Sky& other);

	// 初始化、更新和绘制天空
	void					init();
	void					update(const glm::vec3& player_pos, float sun_height);
	void					draw(const Camera& camera, const std::vector<const Light*>& lights) const;

	// 获取天空的光源
	const Light* get_light() const;
};

#endif

#ifndef LIGHT_H
#define LIGHT_H

#include "utils.h"

// 定义光源类

struct Light
{
public:

	// 枚举定义光源类型
	enum class Type { Ambient = 0, Directional = 1, Point = 2 };

private:

	Type		type;		// 光源类型
	glm::vec3	vector;		// 光源的方向或位置
	Color		color;		// 光源的颜色
	float		intensity;	// 光源的强度

public:

	// 构造函数
	Light();
	Light(const Light& other);
	Light(Type type, const glm::vec3& vector, const Color& color = Color(1.f, 1.f, 1.f, 1.f), float intensity = 1.f);

	// 赋值运算符
	Light& operator=(const Light& other);

	// 获取光源类型
	Type		get_type() const;
	// 设置光源类型
	void		set_type(Type type);

	// 获取光源的方向或位置
	glm::vec3	get_vector() const;
	// 设置光源的方向或位置
	void		set_vector(const glm::vec3& vector);

	// 获取光源颜色
	Color		get_color() const;
	// 设置光源颜色
	void		set_color(const Color& color);

	// 获取光源强度
	float		get_intensity() const;
	// 设置光源强度
	void		set_intensity(float intensity);
};

#endif

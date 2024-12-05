#ifndef MATERIAL_H
#define MATERIAL_H

#include "utils.h"

// 定义材质类

class Material
{
private:

	Color			color;		// 材质的颜色
	float			ambient;	// 环境光的强度
	float			diffuse;	// 漫反射光的强度
	float			specular;	// 高光反射的强度
	float			shininess;	// 光泽度（控制反射的锐利程度）

public:

	// 静态材质实例：块材质、实体材质、水材质
	static Material	block;		// 块的材质
	static Material	entity;		// 实体的材质
	static Material	water;		// 水的材质

	// 默认构造函数
	Material();
	Material(const Material& other);
	Material(const Color& color, float ambient, float diffuse, float specular, float shininess);

	// 赋值运算符
	Material& operator=(const Material& other);

	// 获取和设置材质的各个属性
	Color			get_color() const;
	void			set_color(const Color& color);
	float			get_ambient() const;
	void			set_ambient(float ambient);
	float			get_diffuse() const;
	void			set_diffuse(float diffuse);
	float			get_specular() const;
	void			set_specular(float specular);
	float			get_shininess() const;
	void			set_shininess(float shininess);
};

#endif

#ifndef MESH_H
#define MESH_H

#include "utils.h"

class Skin;
class Block;
class Entity;

// 定义一个网格类

class Mesh
{
private:

	std::vector<float>	positions;		// 顶点位置
	std::vector<float>	normals;		// 法向量
	std::vector<float>	texcoords;		// 纹理坐标

public:

	// 静态常量网格对象，用于常见的几何体
	static const Mesh	circle_64;		// 半径64的圆
	static const Mesh	cone_64;		// 半径64的圆锥，带有64个纬度
	static const Mesh	cube;			// 立方体
	static const Mesh	empty_cube;		// 只带有边框的立方体
	static const Mesh	cylinder_64;	// 半径64的圆柱，带有64个纬度
	static const Mesh	null;			// 空网格
	static const Mesh	sphere_64;		// 半径64的球体，带有64个纬度和64个经度
	static const Mesh	square;			// 正方形
	static const Mesh	screen;			// 屏幕网格

	// 构造函数
	Mesh();
	Mesh(const Mesh& other);

	// 赋值运算符
	Mesh& operator=(const Mesh& other);
	// 追加运算符
	Mesh& operator+=(const Mesh& other);
	// 加法运算符
	Mesh				operator+(const Mesh& other);

	// 获取顶点位置、法线、纹理坐标的指针
	const float* get_positions() const;
	const float* get_normals() const;
	const float* get_texcoords() const;

	// 获取数据大小和各部分的大小
	uint32_t			get_data_size() const;
	uint32_t			get_positions_size() const;
	uint32_t			get_normals_size() const;
	uint32_t			get_texcoords_size() const;
	uint32_t			get_nb_vertices() const;

	// 清空网格数据
	void				clear();

	// 静态方法：生成常见几何形状的网格
	static Mesh			Circle(uint16_t nb_edges);
	static Mesh			Cone(uint16_t nb_lattitudes);
	static Mesh			Cube();
	static Mesh			EmptyCube();
	static Mesh			Cylinder(uint16_t nb_lattitudes);
	static Mesh			Sphere(uint16_t nb_latitudes, uint16_t nb_longitudes);
	static Mesh			Square();
	static Mesh			Screen();

	// 友元类：允许这些类访问Mesh的私有成员
	friend				Block;
	friend				Skin;
	friend				Entity;
	friend Mesh			operator*(const glm::mat4& matrix, const Mesh& mesh);
};

// 立方体的结构体，定义了面和点的数量
struct Cube
{
	struct Face
	{
		static constexpr uint8_t	nb_points = 6;	// 每个面上的点数
	};

	static constexpr uint8_t		nb_faces = 6;	// 立方体的面数
	static constexpr uint8_t		nb_points = 36;	// 立方体的点数
};

// 运算符重载：矩阵与网格的乘法操作
Mesh				operator*(const glm::mat4& matrix, const Mesh& mesh);
// 获取根据方向调整的纹理坐标
std::vector<float>	oriented_top_texcoord(uint8_t orientation);

#endif

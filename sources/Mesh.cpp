#include "Mesh.h"

const Mesh	Mesh::circle_64 = Mesh::Circle(64);
const Mesh	Mesh::cone_64 = Mesh::Cone(64);
const Mesh	Mesh::cube = Mesh::Cube();
const Mesh	Mesh::empty_cube = Mesh::EmptyCube();
const Mesh	Mesh::cylinder_64 = Mesh::Cylinder(64);
const Mesh	Mesh::null = Mesh();
const Mesh	Mesh::sphere_64 = Mesh::Sphere(64, 64);
const Mesh	Mesh::square = Mesh::Square();
const Mesh	Mesh::screen = Mesh::Screen();

// 创建一个网格

Mesh::Mesh()
{
	positions.clear();
	normals.clear();
	texcoords.clear();
}

// 从另一个网格创建一个网格

Mesh::Mesh(const Mesh& other)
{
	*this = other;
}

// 赋值运算符

Mesh& Mesh::operator=(const Mesh& other)
{
	positions = other.positions;
	normals = other.normals;
	texcoords = other.texcoords;

	return *this;
}

// 加法运算符

Mesh& Mesh::operator+=(const Mesh& other)
{
	for (float position : other.positions)
		positions.push_back(position);

	for (float normal : other.normals)
		normals.push_back(normal);

	for (float texcoord : other.texcoords)
		texcoords.push_back(texcoord);

	return *this;
}

// 加法运算符
Mesh Mesh::operator+(const Mesh& other)
{
	Mesh mesh;

	for (float position : positions)
		mesh.positions.push_back(position);

	for (float normal : normals)
		mesh.normals.push_back(normal);

	for (float texcoord : texcoords)
		mesh.texcoords.push_back(texcoord);

	for (float position : other.positions)
		mesh.positions.push_back(position);

	for (float normal : other.normals)
		mesh.normals.push_back(normal);

	for (float texcoord : other.texcoords)
		mesh.texcoords.push_back(texcoord);

	return mesh;
}

// 获取位置数据

const float* Mesh::get_positions() const
{
	return positions.data();
}

// 获取法线数据

const float* Mesh::get_normals() const
{
	return normals.data();
}

// 获取纹理坐标数据

const float* Mesh::get_texcoords() const
{
	return texcoords.data();
}

// 获取数据大小（以字节为单位）

uint32_t Mesh::get_data_size() const
{
	return (positions.size() + normals.size() + texcoords.size()) * sizeof(float);
}

// 获取位置数据的大小（以字节为单位）

uint32_t Mesh::get_positions_size() const
{
	return positions.size() * sizeof(float);
}

// 获取法线数据的大小（以字节为单位）

uint32_t Mesh::get_normals_size() const
{
	return normals.size() * sizeof(float);
}

// 获取纹理坐标数据的大小（以字节为单位）

uint32_t Mesh::get_texcoords_size() const
{
	return texcoords.size() * sizeof(float);
}

// 获取顶点数量

uint32_t Mesh::get_nb_vertices() const
{
	return positions.size() / 3;
}

// 清空网格数据

void Mesh::clear()
{
	positions.clear();
	normals.clear();
	texcoords.clear();
}

// 创建一个圆形
Mesh Mesh::Circle(uint16_t nb_edges)
{
	Mesh mesh;

	mesh.positions.resize(9 * nb_edges, 0.f);
	mesh.normals.resize(9 * nb_edges, 0.f);
	mesh.texcoords.resize(6 * nb_edges, 0.f);

	for (uint16_t i = 0; i < nb_edges; i++)
	{
		float pos[] =
		{
			(float)cos(i * 2.f * pi / nb_edges), (float)sin(i * 2.f * pi / nb_edges), 0.f,
			0.f, 0.f, 0.f,
			(float)cos((i + 1) * 2.f * pi / nb_edges), (float)sin((i + 1) * 2.f * pi / nb_edges), 0.f
		};

		for (uint16_t j = 0; j < 9; j++)
			mesh.positions[9 * i + j] = 0.5f * pos[j];

		for (uint16_t j = 0; j < 3; j++)
			for (uint16_t k = 0; k < 2; k++)
				mesh.texcoords[6 * i + 2 * j + k] = mesh.positions[9 * i + 3 * j + k] + 0.5f;

		for (uint16_t j = 0; j < 3; j++)
		{
			float normal[] = { 0.f, 0.f, 1.f };

			for (uint16_t k = 0; k < 3; k++)
				mesh.normals[9 * i + 3 * j + k] = normal[k];
		}
	}

	return mesh;
}

// 创建一个圆锥
Mesh Mesh::Cone(uint16_t nb_lattitudes)
{
	Mesh mesh;

	float radius = 0.5f;
	mesh.positions.resize(3 * 6 * nb_lattitudes, 0.f);
	mesh.normals.resize(3 * 6 * nb_lattitudes, 0.f);
	mesh.texcoords.resize(2 * 6 * nb_lattitudes, 0.f);

	for (uint16_t i = 0; i < nb_lattitudes; i++)
	{
		double pos[] =
		{
			radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), -1.f / 2.f,
			radius * cos((i + 1) * 2.f * pi / nb_lattitudes), radius * sin((i + 1) * 2.f * pi / nb_lattitudes), -1.f / 2.f,
			cos((i + 1) * 2.f * pi / nb_lattitudes), sin((i + 1) * 2.f * pi / nb_lattitudes), 1.f / 2.f,

			radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), -1.f / 2.f,
			cos((i + 1) * 2.f * pi / nb_lattitudes), sin((i + 1) * 2 * pi / nb_lattitudes), 1.f / 2.f,
			cos(i * 2.f * pi / nb_lattitudes), sin(i * 2.f * pi / nb_lattitudes), 1.f / 2.f
		};

		double uvPos[] =
		{
			i / (double)nb_lattitudes, 0.f,
			(i + 1) / (double)nb_lattitudes, 0.f,
			(i + 1) / (double)nb_lattitudes, 1.f,

			i / (double)nb_lattitudes, 0.f,
			(i + 1) / (double)nb_lattitudes, 1.f,
			i / (double)nb_lattitudes, 1.f
		};

		for (uint16_t j = 0; j < 18; j++)
			mesh.positions[18 * i + j] = pos[j];

		for (uint16_t j = 0; j < 12; j++)
			mesh.texcoords[12 * i + j] = uvPos[j];

		float angle = pi / 4.f;
		glm::vec3 normalI = glm::rotate(glm::mat4(1.f), (float)(i * 2.f * pi / nb_lattitudes), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(cos(angle), 0.f, sin(angle), 1.f);
		glm::vec3 normalI2 = glm::rotate(glm::mat4(1.f), (float)((i + 1.f) * 2.f * pi / nb_lattitudes), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(cos(angle), 0.f, sin(angle), 1.f);

		for (uint16_t j = 0; j < 3; j++)
		{
			mesh.normals[18 * i + 0 + j] = normalI[j];
			mesh.normals[18 * i + 3 + j] = normalI2[j];
			mesh.normals[18 * i + 6 + j] = normalI2[j];
			mesh.normals[18 * i + 9 + j] = normalI[j];
			mesh.normals[18 * i + 12 + j] = normalI2[j];
			mesh.normals[18 * i + 15 + j] = normalI[j];
		}
	}

	return mesh;
}


// 创建一个立方体
Mesh Mesh::Cube()
{
	Mesh mesh;

	mesh.positions =
	{
		// 背面
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		// 前面
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		// 左面
	   -0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f, -0.5f,
	   -0.5f, -0.5f,  0.5f,
	   -0.5f,  0.5f, -0.5f,
	   -0.5f, -0.5f, -0.5f,
	   -0.5f, -0.5f,  0.5f,

	   // 右面
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,

		// 顶面
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		 // 底面
		  0.5f, -0.5f, -0.5f,
		 -0.5f, -0.5f,  0.5f,
		 -0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f,  0.5f,
		 -0.5f, -0.5f,  0.5f
	};

	mesh.normals =
	{
		// 背面
		 0.f, 0.f, -1.f,
		 0.f, 0.f, -1.f,
		 0.f, 0.f, -1.f,
		 0.f, 0.f, -1.f,
		 0.f, 0.f, -1.f,
		 0.f, 0.f, -1.f,

		 // 前面
		  0.f, 0.f, 1.f,
		  0.f, 0.f, 1.f,
		  0.f, 0.f, 1.f,
		  0.f, 0.f, 1.f,
		  0.f, 0.f, 1.f,
		  0.f, 0.f, 1.f,

		  // 左面
		  -1.f, 0.f, 0.f,
		  -1.f, 0.f, 0.f,
		  -1.f, 0.f, 0.f,
		  -1.f, 0.f, 0.f,
		  -1.f, 0.f, 0.f,
		  -1.f, 0.f, 0.f,

		  // 右面
		   1.f, 0.f, 0.f,
		   1.f, 0.f, 0.f,
		   1.f, 0.f, 0.f,
		   1.f, 0.f, 0.f,
		   1.f, 0.f, 0.f,
		   1.f, 0.f, 0.f,

		   // 顶面
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,

			// 底面
			 0.f, -1.f, 0.f,
			 0.f, -1.f, 0.f,
			 0.f, -1.f, 0.f,
			 0.f, -1.f, 0.f,
			 0.f, -1.f, 0.f,
			 0.f, -1.f, 0.f
	};

	mesh.texcoords =
	{
		// 背面
		1.f, 0.f,
		0.f, 0.f,
		1.f, 1.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,

		// 前面
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f,
		0.f, 1.f,

		// 左面
		1.f, 0.f,
		0.f, 0.f,
		1.f, 1.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,

		// 右面
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f,
		0.f, 1.f,

		// 顶面
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,

		// 底面
		0.f, 0.f,
		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f
	};

	return mesh;
}


// 创建一个只有边框的立方体
Mesh Mesh::EmptyCube()
{
	Mesh mesh;

	mesh.positions =
	{
		// 后面
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,

		// 前面
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		// 顶部
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,

		 // 底部
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f
	};

	mesh.normals =
	{
		// 后面
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,

		// 前面
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,

		// 顶部
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,

		// 底部
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f
	};

	mesh.texcoords =
	{
		// 后面
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,

		// 前面
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,

		// 顶部
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,

		// 底部
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f
	};

	return mesh;
}

// 创建一个圆柱体
Mesh Mesh::Cylinder(uint16_t nb_lattitudes)
{
	Mesh mesh;

	float radius = 0.5f;

	mesh.positions.resize(3 * 6 * nb_lattitudes, 0.f);
	mesh.normals.resize(3 * 6 * nb_lattitudes, 0.f);
	mesh.texcoords.resize(2 * 6 * nb_lattitudes, 0.f);

	for (uint16_t i = 0; i < nb_lattitudes; i++)
	{
		// 顶面和底面坐标计算
		double pos[] =
		{
			radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), -1.f / 2.f,
			radius * cos((i + 1) * 2.f * pi / nb_lattitudes), radius * sin((i + 1) * 2 * pi / nb_lattitudes), -1.f / 2.f,
			radius * cos((i + 1) * 2.f * pi / nb_lattitudes), radius * sin((i + 1) * 2.f * pi / nb_lattitudes), 1.f / 2.f,

			radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), -1.f / 2.f,
			radius * cos((i + 1) * 2.f * pi / nb_lattitudes), radius * sin((i + 1) * 2.f * pi / nb_lattitudes), 1.f / 2.f,
			radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), 1.f / 2.f
		};

		// UV坐标
		double uvPos[] =
		{
			i / (double)nb_lattitudes, 0.f,
			(i + 1) / (double)nb_lattitudes, 0.f,
			(i + 1) / (double)nb_lattitudes, 1.f,

			i / (double)nb_lattitudes, 0.f,
			(i + 1) / (double)nb_lattitudes, 1.f,
			i / (double)nb_lattitudes, 1.f
		};

		// 更新顶点位置
		for (uint16_t j = 0; j < 18; j++)
			mesh.positions[18 * i + j] = pos[j];

		// 更新UV坐标
		for (uint16_t j = 0; j < 12; j++)
			mesh.texcoords[12 * i + j] = uvPos[j];

		// 更新法线方向
		for (uint16_t j = 0; j < 6; j++)
		{
			for (uint16_t k = 0; k < 2; k++)
				mesh.normals[18 * i + 3 * j + k] = pos[3 * j + k];

			mesh.normals[18 * i + 3 * j + 2] = 0.f;
		}
	}

	return mesh;
}

// 创建一个球体
Mesh Mesh::Sphere(uint16_t nb_latitudes, uint16_t nb_longitudes)
{
	Mesh mesh;

	float radius = 0.5f;

	// 计算顶点坐标
	glm::vec3* vertexCoord = (glm::vec3*)malloc(nb_longitudes * nb_latitudes * sizeof(glm::vec3));
	glm::vec2* uvCoord = (glm::vec2*)malloc(nb_longitudes * nb_latitudes * sizeof(glm::vec2));

	for (uint16_t i = 0; i < nb_longitudes; i++)
	{
		double theta = 2.f * pi / (nb_longitudes - 1) * i;

		for (uint16_t j = 0; j < nb_latitudes; j++)
		{
			double phi = pi / (nb_latitudes - 1) * j;
			double pos[] = { sin(phi) * sin(theta), cos(phi), cos(theta) * sin(phi) };
			double uvs[] = { i / (double)(nb_longitudes), j / (double)(nb_latitudes) };

			for (uint16_t k = 0; k < 3; k++)
				vertexCoord[i * nb_latitudes + j][k] = radius * pos[k];

			for (uint16_t k = 0; k < 2; k++)
				uvCoord[i * nb_latitudes + j][k] = uvs[k];
		}
	}

	// 计算绘制顺序
	uint16_t* order = (uint16_t*)malloc(nb_longitudes * (nb_latitudes - 1) * sizeof(uint16_t) * 6);

	for (uint16_t i = 0; i < nb_longitudes; i++)
	{
		for (uint16_t j = 0; j < nb_latitudes - 1; j++)
		{
			uint16_t o[] =
			{
				i * nb_latitudes + j, (i + 1) * (nb_latitudes) % (nb_latitudes * nb_longitudes) + (j + 1) % nb_latitudes, (i + 1) * (nb_latitudes) % (nb_latitudes * nb_longitudes) + j,
				i * nb_latitudes + j, i * (nb_latitudes)+(j + 1) % nb_latitudes, (i + 1) * (nb_latitudes) % (nb_latitudes * nb_longitudes) + (j + 1) % nb_latitudes
			};

			for (uint16_t k = 0; k < 6; k++)
				order[(nb_latitudes - 1) * i * 6 + j * 6 + k] = o[k];
		}
	}

	// 合并所有数据
	mesh.positions.resize(nb_longitudes * (nb_latitudes - 1) * 6 * 3, 0.f);
	mesh.normals.resize(nb_longitudes * (nb_latitudes - 1) * 6 * 3, 0.f);
	mesh.texcoords.resize(nb_longitudes * (nb_latitudes - 1) * 6 * 2, 0.f);

	for (uint16_t i = 0; i < nb_latitudes * (nb_longitudes - 1) * 6; i++)
	{
		uint16_t indice = order[i];

		for (uint16_t j = 0; j < 3; j++)
		{
			mesh.positions[3 * i + j] = vertexCoord[indice][j];
			mesh.normals[3 * i + j] = glm::normalize(vertexCoord[indice])[j];
		}

		for (uint16_t j = 0; j < 2; j++)
			mesh.texcoords[2 * i + j] = uvCoord[indice][j];
	}

	return mesh;
}

// 创建一个正方形
Mesh Mesh::Square()
{
	Mesh mesh;

	mesh.positions =
	{
		 0.5f,  0.5f,  0.f,
		-0.5f,  0.5f,  0.f,
		-0.5f, -0.5f,  0.f,
		 0.5f, -0.5f,  0.f,
		 0.5f,  0.5f,  0.f,
		-0.5f, -0.5f,  0.f
	};

	mesh.normals =
	{
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f,
		0.f, 0.f, 1.f
	};

	mesh.texcoords =
	{
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f,
		0.f, 1.f
	};

	return mesh;
}

// 创建一个屏幕
Mesh Mesh::Screen()
{
	Mesh mesh;

	mesh.positions =
	{
		 1.f,  1.f,  0.f,
		-1.f,  1.f,  0.f,
		-1.f, -1.f,  0.f,
		 1.f, -1.f,  0.f,
		 1.f,  1.f,  0.f,
		-1.f, -1.f,  0.f
	};

	mesh.normals =
	{
		0.f, 0.f, -1.f,
		0.f, 0.f, -1.f,
		0.f, 0.f, -1.f,
		0.f, 0.f, -1.f,
		0.f, 0.f, -1.f,
		0.f, 0.f, -1.f
	};

	mesh.texcoords =
	{
		1.f, 1.f,
		0.f, 1.f,
		0.f, 0.f,
		1.f, 0.f,
		1.f, 1.f,
		0.f, 0.f
	};

	return mesh;
}

// 将一个矩阵应用到网格的每个点上
Mesh operator*(const glm::mat4& matrix, const Mesh& mesh)
{
	Mesh result;

	for (uint16_t i = 0; i < mesh.positions.size(); i += 3)
	{
		glm::vec3 position(mesh.positions[i], mesh.positions[i + 1], mesh.positions[i + 2]);

		position = matrix * position;

		result.positions.push_back(position.x);
		result.positions.push_back(position.y);
		result.positions.push_back(position.z);
	}

	glm::mat3 normals_matrice = glm::transpose(glm::inverse(glm::mat3(matrix)));

	for (uint32_t i = 0; i < mesh.normals.size(); i += 3)
	{
		glm::vec3 normal(mesh.normals[i], mesh.normals[i + 1], mesh.normals[i + 2]);

		normal = glm::normalize(normals_matrice * normal);

		result.normals.push_back(normal.x);
		result.normals.push_back(normal.y);
		result.normals.push_back(normal.z);
	}

	result.texcoords = mesh.texcoords;

	return result;
}

// 给定一个方向，返回一个立方体顶部的纹理坐标
std::vector<float> oriented_top_texcoord(uint8_t orientation)
{
	switch (orientation)
	{
	case 0:
		return
		{
			1.f, 0.f,
			0.f, 0.f,
			0.f, 1.f,
			1.f, 0.f,
			0.f, 1.f,
			1.f, 1.f
		};

	case 1:
		return
		{
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			0.f, 0.f,
			1.f, 1.f,
			1.f, 0.f
		};

	case 2:
		return
		{
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f,
			0.f, 1.f,
			1.f, 0.f,
			0.f, 0.f
		};

	case 3:
		return
		{
			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f,
			1.f, 1.f,
			0.f, 0.f,
			0.f, 1.f
		};

	default:
		return {};
	}
}

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

// ����һ������

Mesh::Mesh()
{
	positions.clear();
	normals.clear();
	texcoords.clear();
}

// ����һ�����񴴽�һ������

Mesh::Mesh(const Mesh& other)
{
	*this = other;
}

// ��ֵ�����

Mesh& Mesh::operator=(const Mesh& other)
{
	positions = other.positions;
	normals = other.normals;
	texcoords = other.texcoords;

	return *this;
}

// �ӷ������

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

// �ӷ������
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

// ��ȡλ������

const float* Mesh::get_positions() const
{
	return positions.data();
}

// ��ȡ��������

const float* Mesh::get_normals() const
{
	return normals.data();
}

// ��ȡ������������

const float* Mesh::get_texcoords() const
{
	return texcoords.data();
}

// ��ȡ���ݴ�С�����ֽ�Ϊ��λ��

uint32_t Mesh::get_data_size() const
{
	return (positions.size() + normals.size() + texcoords.size()) * sizeof(float);
}

// ��ȡλ�����ݵĴ�С�����ֽ�Ϊ��λ��

uint32_t Mesh::get_positions_size() const
{
	return positions.size() * sizeof(float);
}

// ��ȡ�������ݵĴ�С�����ֽ�Ϊ��λ��

uint32_t Mesh::get_normals_size() const
{
	return normals.size() * sizeof(float);
}

// ��ȡ�����������ݵĴ�С�����ֽ�Ϊ��λ��

uint32_t Mesh::get_texcoords_size() const
{
	return texcoords.size() * sizeof(float);
}

// ��ȡ��������

uint32_t Mesh::get_nb_vertices() const
{
	return positions.size() / 3;
}

// �����������

void Mesh::clear()
{
	positions.clear();
	normals.clear();
	texcoords.clear();
}

// ����һ��Բ��
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

// ����һ��Բ׶
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


// ����һ��������
Mesh Mesh::Cube()
{
	Mesh mesh;

	mesh.positions =
	{
		// ����
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		// ǰ��
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		// ����
	   -0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f, -0.5f,
	   -0.5f, -0.5f,  0.5f,
	   -0.5f,  0.5f, -0.5f,
	   -0.5f, -0.5f, -0.5f,
	   -0.5f, -0.5f,  0.5f,

	   // ����
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,

		// ����
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		 // ����
		  0.5f, -0.5f, -0.5f,
		 -0.5f, -0.5f,  0.5f,
		 -0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f,  0.5f,
		 -0.5f, -0.5f,  0.5f
	};

	mesh.normals =
	{
		// ����
		 0.f, 0.f, -1.f,
		 0.f, 0.f, -1.f,
		 0.f, 0.f, -1.f,
		 0.f, 0.f, -1.f,
		 0.f, 0.f, -1.f,
		 0.f, 0.f, -1.f,

		 // ǰ��
		  0.f, 0.f, 1.f,
		  0.f, 0.f, 1.f,
		  0.f, 0.f, 1.f,
		  0.f, 0.f, 1.f,
		  0.f, 0.f, 1.f,
		  0.f, 0.f, 1.f,

		  // ����
		  -1.f, 0.f, 0.f,
		  -1.f, 0.f, 0.f,
		  -1.f, 0.f, 0.f,
		  -1.f, 0.f, 0.f,
		  -1.f, 0.f, 0.f,
		  -1.f, 0.f, 0.f,

		  // ����
		   1.f, 0.f, 0.f,
		   1.f, 0.f, 0.f,
		   1.f, 0.f, 0.f,
		   1.f, 0.f, 0.f,
		   1.f, 0.f, 0.f,
		   1.f, 0.f, 0.f,

		   // ����
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 1.f, 0.f,

			// ����
			 0.f, -1.f, 0.f,
			 0.f, -1.f, 0.f,
			 0.f, -1.f, 0.f,
			 0.f, -1.f, 0.f,
			 0.f, -1.f, 0.f,
			 0.f, -1.f, 0.f
	};

	mesh.texcoords =
	{
		// ����
		1.f, 0.f,
		0.f, 0.f,
		1.f, 1.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,

		// ǰ��
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f,
		0.f, 1.f,

		// ����
		1.f, 0.f,
		0.f, 0.f,
		1.f, 1.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,

		// ����
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f,
		0.f, 1.f,

		// ����
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,

		// ����
		0.f, 0.f,
		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f
	};

	return mesh;
}


// ����һ��ֻ�б߿��������
Mesh Mesh::EmptyCube()
{
	Mesh mesh;

	mesh.positions =
	{
		// ����
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,

		// ǰ��
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		// ����
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,

		 // �ײ�
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
		// ����
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,

		// ǰ��
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,

		// ����
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		1.f, 0.f, 0.f,

		// �ײ�
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
		// ����
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,

		// ǰ��
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,

		// ����
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f,

		// �ײ�
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

// ����һ��Բ����
Mesh Mesh::Cylinder(uint16_t nb_lattitudes)
{
	Mesh mesh;

	float radius = 0.5f;

	mesh.positions.resize(3 * 6 * nb_lattitudes, 0.f);
	mesh.normals.resize(3 * 6 * nb_lattitudes, 0.f);
	mesh.texcoords.resize(2 * 6 * nb_lattitudes, 0.f);

	for (uint16_t i = 0; i < nb_lattitudes; i++)
	{
		// ����͵����������
		double pos[] =
		{
			radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), -1.f / 2.f,
			radius * cos((i + 1) * 2.f * pi / nb_lattitudes), radius * sin((i + 1) * 2 * pi / nb_lattitudes), -1.f / 2.f,
			radius * cos((i + 1) * 2.f * pi / nb_lattitudes), radius * sin((i + 1) * 2.f * pi / nb_lattitudes), 1.f / 2.f,

			radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), -1.f / 2.f,
			radius * cos((i + 1) * 2.f * pi / nb_lattitudes), radius * sin((i + 1) * 2.f * pi / nb_lattitudes), 1.f / 2.f,
			radius * cos(i * 2.f * pi / nb_lattitudes), radius * sin(i * 2.f * pi / nb_lattitudes), 1.f / 2.f
		};

		// UV����
		double uvPos[] =
		{
			i / (double)nb_lattitudes, 0.f,
			(i + 1) / (double)nb_lattitudes, 0.f,
			(i + 1) / (double)nb_lattitudes, 1.f,

			i / (double)nb_lattitudes, 0.f,
			(i + 1) / (double)nb_lattitudes, 1.f,
			i / (double)nb_lattitudes, 1.f
		};

		// ���¶���λ��
		for (uint16_t j = 0; j < 18; j++)
			mesh.positions[18 * i + j] = pos[j];

		// ����UV����
		for (uint16_t j = 0; j < 12; j++)
			mesh.texcoords[12 * i + j] = uvPos[j];

		// ���·��߷���
		for (uint16_t j = 0; j < 6; j++)
		{
			for (uint16_t k = 0; k < 2; k++)
				mesh.normals[18 * i + 3 * j + k] = pos[3 * j + k];

			mesh.normals[18 * i + 3 * j + 2] = 0.f;
		}
	}

	return mesh;
}

// ����һ������
Mesh Mesh::Sphere(uint16_t nb_latitudes, uint16_t nb_longitudes)
{
	Mesh mesh;

	float radius = 0.5f;

	// ���㶥������
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

	// �������˳��
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

	// �ϲ���������
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

// ����һ��������
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

// ����һ����Ļ
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

// ��һ������Ӧ�õ������ÿ������
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

// ����һ�����򣬷���һ�������嶥������������
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

#ifndef MESH_H
#define MESH_H

#include "utils.h"

class Skin;
class Block;
class Entity;

// ����һ��������

class Mesh
{
private:

	std::vector<float>	positions;		// ����λ��
	std::vector<float>	normals;		// ������
	std::vector<float>	texcoords;		// ��������

public:

	// ��̬��������������ڳ����ļ�����
	static const Mesh	circle_64;		// �뾶64��Բ
	static const Mesh	cone_64;		// �뾶64��Բ׶������64��γ��
	static const Mesh	cube;			// ������
	static const Mesh	empty_cube;		// ֻ���б߿��������
	static const Mesh	cylinder_64;	// �뾶64��Բ��������64��γ��
	static const Mesh	null;			// ������
	static const Mesh	sphere_64;		// �뾶64�����壬����64��γ�Ⱥ�64������
	static const Mesh	square;			// ������
	static const Mesh	screen;			// ��Ļ����

	// ���캯��
	Mesh();
	Mesh(const Mesh& other);

	// ��ֵ�����
	Mesh& operator=(const Mesh& other);
	// ׷�������
	Mesh& operator+=(const Mesh& other);
	// �ӷ������
	Mesh				operator+(const Mesh& other);

	// ��ȡ����λ�á����ߡ����������ָ��
	const float* get_positions() const;
	const float* get_normals() const;
	const float* get_texcoords() const;

	// ��ȡ���ݴ�С�͸����ֵĴ�С
	uint32_t			get_data_size() const;
	uint32_t			get_positions_size() const;
	uint32_t			get_normals_size() const;
	uint32_t			get_texcoords_size() const;
	uint32_t			get_nb_vertices() const;

	// �����������
	void				clear();

	// ��̬���������ɳ���������״������
	static Mesh			Circle(uint16_t nb_edges);
	static Mesh			Cone(uint16_t nb_lattitudes);
	static Mesh			Cube();
	static Mesh			EmptyCube();
	static Mesh			Cylinder(uint16_t nb_lattitudes);
	static Mesh			Sphere(uint16_t nb_latitudes, uint16_t nb_longitudes);
	static Mesh			Square();
	static Mesh			Screen();

	// ��Ԫ�ࣺ������Щ�����Mesh��˽�г�Ա
	friend				Block;
	friend				Skin;
	friend				Entity;
	friend Mesh			operator*(const glm::mat4& matrix, const Mesh& mesh);
};

// ������Ľṹ�壬��������͵������
struct Cube
{
	struct Face
	{
		static constexpr uint8_t	nb_points = 6;	// ÿ�����ϵĵ���
	};

	static constexpr uint8_t		nb_faces = 6;	// �����������
	static constexpr uint8_t		nb_points = 36;	// ������ĵ���
};

// ��������أ�����������ĳ˷�����
Mesh				operator*(const glm::mat4& matrix, const Mesh& mesh);
// ��ȡ���ݷ����������������
std::vector<float>	oriented_top_texcoord(uint8_t orientation);

#endif

#ifndef CHUNK_H
#define CHUNK_H

#include "utils.h"
#include "Block.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "Mesh.h"

#include <array>

class Player;
class World;
class Game;
class Entity;

// ����һ���飨Chunk����

class Chunk
{
public:

	static constexpr uint8_t	size = 16;					// һ����Ŀ��
	static constexpr uint8_t	height = 128;				// һ����ĸ߶�
	static constexpr uint16_t	max_distance = 5 * size;	// ���ص��������

	typedef std::array<std::array<std::array<Block, size>, height>, size> BlockArray;

	// ����ʵ�ֿ�߽��ϵ���ľ���� :(

	/*
	// �ṹ���ʾ����ӵ�Ҷ���б�

	struct LeavesToAdd
	{
		glm::ivec3					chunk;	// Ҷ�����ڵĿ�λ��
		std::vector<glm::ivec3>		leaves;	// ����ӵ�Ҷ��

									LeavesToAdd();
									LeavesToAdd(const glm::ivec3& chunk_position);
									LeavesToAdd(const LeavesToAdd& other);

		LeavesToAdd&				operator=(const LeavesToAdd& other);
	};
	*/

private:

	World* world;						// ָ�������ָ��
	glm::ivec3					position;					// ���λ��
	BlockArray					blocks;						// ���еķ����б�
	uint8_t						local_layer_min;			// ���е���Ͳ�
	uint8_t						local_layer_max;			// ���е���߲�
	uint8_t						layer_min;					// ȫ����Ͳ�
	uint8_t						layer_max;					// ȫ����߲�
	bool						as_updated;					// �Ƿ�����˶���
	bool						as_sent;					// �Ƿ��ѽ����㷢�͵���ɫ��
	std::list<Chunk*>			chunks_around;				// ��Χ�Ŀ�
	Mesh						mesh;						// ����
	VertexBuffer				object;						// OpenGL ���㻺����
	bool						as_water;					// �Ƿ����ˮ

	static VertexBuffer			water_top;					// ˮ�棨����ͼ��
	static VertexBuffer			water_bottom;				// ˮ�棨����ͼ��
	static VertexBuffer			limits;						// ��ı߽�
	//static std::vector<LeavesToAdd>	leaves_to_add;

public:

	Chunk();
	Chunk(const Chunk& other);
	Chunk(const glm::ivec3& position, World* world);

	Chunk& operator=(const Chunk& other);
	Block& operator[](const glm::ivec3& block_pos);

	float						noise(int8_t x, int8_t z, float size, float height, float shift = 0.f);	// ��������
	void						generate_blocks();			// ���ɿ��еķ���
	bool						add_tree(int8_t x, uint8_t y, int8_t z);	// �����
	void						add_leave(int8_t x, uint8_t y, int8_t z, bool update_block = false);	// ���Ҷ��
	void						add_plant(int8_t x, uint8_t y, int8_t z);	// ���ֲ��
	Block* find_block(const glm::ivec3& block_pos);	// ���ҷ���
	void						update_all();				// �������п�
	void						update_edges();				// ���¿�ı�Ե
	void						update_face(uint8_t face_id);	// ����ָ������
	void						generate_mesh();				// ��������
	void						send_mesh();					// ������������
	bool						is_visible(const Camera& camera) const;	// �жϿ��Ƿ�ɼ�
	void						draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;	// ���ƿ�
	void						draw_water(const Camera& camera, const std::vector<const Light*>& lights) const;	// ����ˮ��

	friend						World;
	friend						Block;
	friend						Player;
	friend						Entity;
};

#endif

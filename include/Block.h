#ifndef BLOCK_H
#define BLOCK_H

#include "utils.h"
#include "Mesh.h"

class Chunk;
class World;

typedef std::array<bool, Cube::nb_faces>	FacesShown;			// 0: ����, 1: ǰ��, 2: ����, 3: ����, 4: ����, 5: ����
typedef std::array<uint8_t, Cube::nb_faces>	FacesOrientation;	// 0: ����, 1: ǰ��, 2: ����, 3: ����, 4: ����, 5: ����

// ����һ������

class Block
{
public:

	// ö�ٶ���������

	enum class Type { Air, Grass, Dirt, Stone, Sand, Wood, Leaves, Snow, Weed, TallWeedBottom, TallWeebTop, Tulip, Orchid, Dandelion };

private:

	Chunk* chunk;												// ָ��ÿ����ڵ� chunk ��ָ��
	FacesShown				faces_shown;										// ��ǰ��ʾ����

	Type					type;												// �������
	glm::ivec3				position;											// ���λ��
	FacesOrientation		faces_orientation;									// ����泯��

	static constexpr float	total_texture_size = 128.f;							// ��������ܴ�С
	static constexpr float	texture_size = 16.f;								// ������������С
	static constexpr float	texture_ratio = texture_size / total_texture_size;	// �������������Դ�С

public:

	static Block			air;												// ������

	Block();
	Block(const Block& other);
	Block(Type type, const glm::ivec3& position, Chunk* chunk);

	Block& operator=(const Block& other);

	bool					is_plant() const;								// �ж��Ƿ�Ϊֲ��
	bool					is_transparent(const Block& block) const;		// �жϸÿ��Ƿ�Ϊ͸����
	bool					is_edge() const;									// �ж��Ƿ�Ϊ��Ե��
	void					set_type(Type type, bool update_block);			// ���ÿ�����Ͳ�ѡ���Ƿ����
	void					update_face(uint8_t face_id);						// ����ָ����
	void					update(bool update_around, uint8_t direction_id = 6);	// ���¿鲢ѡ���Ƿ������Χ��
	void					add_texcoords(uint8_t face_id, uint8_t x, uint8_t y, std::vector<float>& texcoords) const;	// Ϊָ���������������
	void					send_texcoords(uint8_t face_id, std::vector<float>& texcoords) const;	// ����ָ�������������
	void					draw(Mesh& mesh) const;							// ���Ƹÿ�
	void					draw_plant(Mesh& mesh) const;						// ����ֲ���

    // ��ö������ת��Ϊ�ַ��� new
    static std::string type_to_string(Type type)
    {
        switch (type)
        {
        case Type::Air:               return "Air";
        case Type::Grass:             return "Grass";
        case Type::Dirt:              return "Dirt";
        case Type::Stone:             return "Stone";
        case Type::Sand:              return "Sand";
        case Type::Wood:              return "Wood";
        case Type::Leaves:            return "Leaves";
        case Type::Snow:              return "Snow";
        case Type::Weed:              return "Weed";
        case Type::TallWeedBottom:    return "TallWeedBottom";
        case Type::TallWeebTop:       return "TallWeebTop";
        case Type::Tulip:             return "Tulip";
        case Type::Orchid:            return "Orchid";
        case Type::Dandelion:         return "Dandelion";
        default:                      return "Unknown";
        }
    }

	const Chunk& get_chunk() const;								// ��ȡ�ÿ����ڵ� chunk
	Type					get_type() const;								// ��ȡ�������
	glm::ivec3				get_position() const;							// ��ȡ���λ��

	friend					Chunk;
};

#endif

#ifndef BLOCK_H
#define BLOCK_H

#include "utils.h"
#include "Mesh.h"

class Chunk;
class World;

typedef std::array<bool, Cube::nb_faces>	FacesShown;			// 0: 后面, 1: 前面, 2: 左面, 3: 右面, 4: 上面, 5: 下面
typedef std::array<uint8_t, Cube::nb_faces>	FacesOrientation;	// 0: 后面, 1: 前面, 2: 左面, 3: 右面, 4: 上面, 5: 下面

// 定义一个块类

class Block
{
public:

	// 枚举定义块的类型

	enum class Type { Air, Grass, Dirt, Stone, Sand, Wood, Leaves, Snow, Weed, TallWeedBottom, TallWeebTop, Tulip, Orchid, Dandelion };

private:

	Chunk* chunk;												// 指向该块所在的 chunk 的指针
	FacesShown				faces_shown;										// 当前显示的面

	Type					type;												// 块的类型
	glm::ivec3				position;											// 块的位置
	FacesOrientation		faces_orientation;									// 块的面朝向

	static constexpr float	total_texture_size = 128.f;							// 块纹理的总大小
	static constexpr float	texture_size = 16.f;								// 单个块的纹理大小
	static constexpr float	texture_ratio = texture_size / total_texture_size;	// 单个块纹理的相对大小

public:

	static Block			air;												// 空气块

	Block();
	Block(const Block& other);
	Block(Type type, const glm::ivec3& position, Chunk* chunk);

	Block& operator=(const Block& other);

	bool					is_plant() const;								// 判断是否为植物
	bool					is_transparent(const Block& block) const;		// 判断该块是否为透明块
	bool					is_edge() const;									// 判断是否为边缘块
	void					set_type(Type type, bool update_block);			// 设置块的类型并选择是否更新
	void					update_face(uint8_t face_id);						// 更新指定面
	void					update(bool update_around, uint8_t direction_id = 6);	// 更新块并选择是否更新周围块
	void					add_texcoords(uint8_t face_id, uint8_t x, uint8_t y, std::vector<float>& texcoords) const;	// 为指定面添加纹理坐标
	void					send_texcoords(uint8_t face_id, std::vector<float>& texcoords) const;	// 发送指定面的纹理坐标
	void					draw(Mesh& mesh) const;							// 绘制该块
	void					draw_plant(Mesh& mesh) const;						// 绘制植物块

    // 将枚举类型转换为字符串 new
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

	const Chunk& get_chunk() const;								// 获取该块所在的 chunk
	Type					get_type() const;								// 获取块的类型
	glm::ivec3				get_position() const;							// 获取块的位置

	friend					Chunk;
};

#endif

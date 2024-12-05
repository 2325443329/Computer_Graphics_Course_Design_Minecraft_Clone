#ifndef WORLD_H
#define WORLD_H

#include "utils.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Shader.h"

// 常量定义
constexpr uint8_t    average_stone_height = 45;        // 平均石块高度
constexpr uint8_t    above_stone_height = 3;         // 平均土壤高度
constexpr uint8_t    sand_dirt_limit = 32;        // 沙土与草地之间的高度限制
constexpr uint8_t    dirt_stone_limit = 60;        // 草地与山石之间的高度限制
constexpr uint8_t    stone_snow_limit = 80;        // 石块与雪之间的高度限制
constexpr float      water_level = 31.2f;     // 水位高度
constexpr uint8_t    tree_height = 7;         // 树木的高度
constexpr float      gravity = 30.f;      // 重力值
constexpr uint16_t   nb_max_lights = 10;        // 最大光源数量
constexpr uint16_t   nb_max_mobs = 1;        // 最大怪物数量

class Player;
class Block;
class Chunk;
class Mob;

// 表示世界的类
class World
{
private:
    std::list<Chunk*>       chunks;               // 加载的块列表
    std::list<glm::ivec3>   future_chunks_pos;    // 未来块的位置列表（周围的块）
    std::list<Mob*>         mobs;                 // 加载的怪物列表

public:
    uint16_t                seed;                 // 地图的种子

    // 构造函数
    World();
    // 拷贝构造函数
    World(const World& other);
    // 析构函数
    ~World();

    // 赋值运算符
    World& operator=(const World& other);
    // 根据块的位置返回对应的块
    Block& operator[](const glm::ivec3& block_pos) const;

    // 添加一个新的块
    void add_chunk(const glm::ivec3& chunk_pos);
    // 移除一个块
    void remove_chunk(Chunk* chunk);
    // 将块的位置转换为对应的区块位置
    glm::ivec3 block_to_chunk(const glm::ivec3& block_pos) const;
    // 查找指定位置的区块
    Chunk* find_chunk(const glm::ivec3& chunk_pos) const;
    // 获取指定区块周围的区块数量
    uint8_t nb_chunks_around(const glm::ivec3& chunk_pos) const;
    // 获取玩家和指定区块之间的距离
    float get_distance(const glm::vec3& player_pos, const glm::ivec3& chunk_pos) const;
    // 获取玩家选择的块
    Block* get_selected_block(const Player& player);

    // 初始化世界，使用指定的种子和玩家位置
    void init(const int64_t& seed, const glm::vec3& player_pos);
    // 根据玩家的位置生成世界
    void generate(const glm::vec3& player_pos);
    // 生成世界的网格
    void generate_meshes();
    // 发送网格数据到图形引擎
    void send_meshes();
    // 更新怪物状态
    void update_mobs(const glm::vec3& player_pos);
    // 绘制世界（包括块和物体）
    void draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000)) const;
    // 绘制水面
    void draw_water(const Camera& camera, const std::vector<const Light*>& lights) const;
    // 绘制怪物
    void draw_mobs(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000)) const;
    // 绘制调试信息
    void draw_debug(const Camera& camera) const;
};

#endif

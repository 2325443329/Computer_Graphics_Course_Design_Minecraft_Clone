#ifndef WORLD_H
#define WORLD_H

#include "utils.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Shader.h"

// ��������
constexpr uint8_t    average_stone_height = 45;        // ƽ��ʯ��߶�
constexpr uint8_t    above_stone_height = 3;         // ƽ�������߶�
constexpr uint8_t    sand_dirt_limit = 32;        // ɳ����ݵ�֮��ĸ߶�����
constexpr uint8_t    dirt_stone_limit = 60;        // �ݵ���ɽʯ֮��ĸ߶�����
constexpr uint8_t    stone_snow_limit = 80;        // ʯ����ѩ֮��ĸ߶�����
constexpr float      water_level = 31.2f;     // ˮλ�߶�
constexpr uint8_t    tree_height = 7;         // ��ľ�ĸ߶�
constexpr float      gravity = 30.f;      // ����ֵ
constexpr uint16_t   nb_max_lights = 10;        // ����Դ����
constexpr uint16_t   nb_max_mobs = 1;        // ����������

class Player;
class Block;
class Chunk;
class Mob;

// ��ʾ�������
class World
{
private:
    std::list<Chunk*>       chunks;               // ���صĿ��б�
    std::list<glm::ivec3>   future_chunks_pos;    // δ�����λ���б���Χ�Ŀ飩
    std::list<Mob*>         mobs;                 // ���صĹ����б�

public:
    uint16_t                seed;                 // ��ͼ������

    // ���캯��
    World();
    // �������캯��
    World(const World& other);
    // ��������
    ~World();

    // ��ֵ�����
    World& operator=(const World& other);
    // ���ݿ��λ�÷��ض�Ӧ�Ŀ�
    Block& operator[](const glm::ivec3& block_pos) const;

    // ���һ���µĿ�
    void add_chunk(const glm::ivec3& chunk_pos);
    // �Ƴ�һ����
    void remove_chunk(Chunk* chunk);
    // �����λ��ת��Ϊ��Ӧ������λ��
    glm::ivec3 block_to_chunk(const glm::ivec3& block_pos) const;
    // ����ָ��λ�õ�����
    Chunk* find_chunk(const glm::ivec3& chunk_pos) const;
    // ��ȡָ��������Χ����������
    uint8_t nb_chunks_around(const glm::ivec3& chunk_pos) const;
    // ��ȡ��Һ�ָ������֮��ľ���
    float get_distance(const glm::vec3& player_pos, const glm::ivec3& chunk_pos) const;
    // ��ȡ���ѡ��Ŀ�
    Block* get_selected_block(const Player& player);

    // ��ʼ�����磬ʹ��ָ�������Ӻ����λ��
    void init(const int64_t& seed, const glm::vec3& player_pos);
    // ������ҵ�λ����������
    void generate(const glm::vec3& player_pos);
    // �������������
    void generate_meshes();
    // �����������ݵ�ͼ������
    void send_meshes();
    // ���¹���״̬
    void update_mobs(const glm::vec3& player_pos);
    // �������磨����������壩
    void draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000)) const;
    // ����ˮ��
    void draw_water(const Camera& camera, const std::vector<const Light*>& lights) const;
    // ���ƹ���
    void draw_mobs(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000)) const;
    // ���Ƶ�����Ϣ
    void draw_debug(const Camera& camera) const;
};

#endif

#ifndef VERTEXOBJECT_H
#define VERTEXOBJECT_H

#include "libraries.h"
#include "Mesh.h"
#include "Shader.h"

// ����������͵�ö��

enum class DrawType {
    Triangles = GL_TRIANGLES, // ����������
    Lines = GL_LINES,         // �����߶�
    Points = GL_POINTS        // ���Ƶ�
};

// ����Ҫ���͵���ɫ������������ö��

enum class DataType : uint8_t {
    Positions = 1,            // ����λ��
    Normals = 2,              // ����
    TexCoords = 4,            // ��������
    All = 7                   // �������ݣ�λ�á����ߺ��������꣩
};

// ����һ�����㻺�����࣬���ڹ���OpenGL�Ķ�������

class VertexBuffer
{
private:

    Shader* shader;         // ָ��ǰʹ�õ���ɫ����ָ��
    std::shared_ptr<GLuint>  vbo;            // ���㻺�����VBO����ID
    std::shared_ptr<GLuint>  vao;            // �����������VAO����ID
    uint32_t                 nb_vertices;    // ��������

public:

    VertexBuffer();                          // Ĭ�Ϲ��캯��
    VertexBuffer(const VertexBuffer& other); // �������캯��
    VertexBuffer(Shader& shader);            // ����ɫ���Ĺ��캯��
    VertexBuffer(Shader& shader, const Mesh& mesh, DataType data_sent = DataType::All); // ����ɫ��������Ĺ��캯��
    ~VertexBuffer();                        // ��������

    VertexBuffer& operator=(const VertexBuffer& other); // ������ֵ�����

    void set_shader(Shader& shader);                           // ���õ�ǰ����ɫ��
    void send_data(Shader& shader, const Mesh& mesh, DataType data_sent = DataType::All); // �������ݵ���ɫ��
    void send_data(const Mesh& mesh, DataType data_sent = DataType::All); // �������ݵ���ɫ����û��ָ����ɫ��ʱʹ�õ�ǰ��ɫ����

    // ����uniform���͵�����
    void send_uniform(const std::string& name, float number) const;  // ���͵���������
    void send_uniform(const std::string& name, int number) const;    // ���͵�������
    void send_uniform(const std::string& name, const std::vector<float>& numbers) const; // ���͸���������
    void send_uniform(const std::string& name, const std::vector<int>& numbers) const;   // ������������
    void send_uniform_2(const std::string& name, const std::vector<float>& numbers) const; // ���͸��������飨��СΪ2��
    void send_uniform_2(const std::string& name, const std::vector<int>& numbers) const;   // �����������飨��СΪ2��
    void send_uniform_3(const std::string& name, const std::vector<float>& numbers) const; // ���͸��������飨��СΪ3��
    void send_uniform_3(const std::string& name, const std::vector<int>& numbers) const;   // �����������飨��СΪ3��
    void send_uniform_4(const std::string& name, const std::vector<float>& numbers) const; // ���͸��������飨��СΪ4��
    void send_uniform_4(const std::string& name, const std::vector<int>& numbers) const;   // �����������飨��СΪ4��

    void send_uniform(const std::string& name, const glm::vec2& vector) const; // ���Ͷ�ά����
    void send_uniform(const std::string& name, const glm::vec3& vector) const; // ������ά����
    void send_uniform(const std::string& name, const Color& color) const;     // ������ɫֵ

    void send_uniform(const std::string& name, const std::vector<glm::vec2>& vectors) const; // ���Ͷ�ά��������
    void send_uniform(const std::string& name, const std::vector<glm::vec3>& vectors) const; // ������ά��������
    void send_uniform(const std::string& name, const std::vector<Color>& color) const;       // ������ɫ����

    void send_uniform(const std::string& name, const glm::mat2& matrix) const; // ���Ͷ�ά����
    void send_uniform(const std::string& name, const glm::mat3& matrix) const; // ������ά����
    void send_uniform(const std::string& name, const glm::mat4& matrix) const; // ������ά����

    void send_texture(const std::string& name, uint8_t texture_index) const; // ������������

    void draw(DrawType draw_type = DrawType::Triangles) const; // ���ƶ������ݣ�Ĭ�ϻ���������

    bool is_valid() const;    // �ж϶��㻺�����Ƿ���Ч
    void bind() const;       // �󶨶��㻺����
    static void unbind();    // ��󶥵㻺����
};

// ��������أ����ڲ���DataTypeö��

DataType operator&(DataType type_1, DataType type_2); // ��λ�����
DataType operator|(DataType type_1, DataType type_2); // ��λ�����
DataType operator^(DataType type_1, DataType type_2); // ��λ������
DataType operator~(DataType type);                    // ��λȡ������
DataType operator<<(DataType type, uint8_t shift);    // ��λ���Ʋ���
DataType operator>>(DataType type, uint8_t shift);    // ��λ���Ʋ���

#endif

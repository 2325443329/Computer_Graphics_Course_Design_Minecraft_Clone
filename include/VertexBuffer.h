#ifndef VERTEXOBJECT_H
#define VERTEXOBJECT_H

#include "libraries.h"
#include "Mesh.h"
#include "Shader.h"

// 定义绘制类型的枚举

enum class DrawType {
    Triangles = GL_TRIANGLES, // 绘制三角形
    Lines = GL_LINES,         // 绘制线段
    Points = GL_POINTS        // 绘制点
};

// 定义要发送到着色器的数据类型枚举

enum class DataType : uint8_t {
    Positions = 1,            // 顶点位置
    Normals = 2,              // 法线
    TexCoords = 4,            // 纹理坐标
    All = 7                   // 所有数据（位置、法线和纹理坐标）
};

// 定义一个顶点缓冲区类，用于管理OpenGL的顶点数据

class VertexBuffer
{
private:

    Shader* shader;         // 指向当前使用的着色器的指针
    std::shared_ptr<GLuint>  vbo;            // 顶点缓冲对象（VBO）的ID
    std::shared_ptr<GLuint>  vao;            // 顶点数组对象（VAO）的ID
    uint32_t                 nb_vertices;    // 顶点数量

public:

    VertexBuffer();                          // 默认构造函数
    VertexBuffer(const VertexBuffer& other); // 拷贝构造函数
    VertexBuffer(Shader& shader);            // 带着色器的构造函数
    VertexBuffer(Shader& shader, const Mesh& mesh, DataType data_sent = DataType::All); // 带着色器和网格的构造函数
    ~VertexBuffer();                        // 析构函数

    VertexBuffer& operator=(const VertexBuffer& other); // 拷贝赋值运算符

    void set_shader(Shader& shader);                           // 设置当前的着色器
    void send_data(Shader& shader, const Mesh& mesh, DataType data_sent = DataType::All); // 发送数据到着色器
    void send_data(const Mesh& mesh, DataType data_sent = DataType::All); // 发送数据到着色器（没有指定着色器时使用当前着色器）

    // 发送uniform类型的数据
    void send_uniform(const std::string& name, float number) const;  // 发送单个浮动数
    void send_uniform(const std::string& name, int number) const;    // 发送单个整数
    void send_uniform(const std::string& name, const std::vector<float>& numbers) const; // 发送浮动数数组
    void send_uniform(const std::string& name, const std::vector<int>& numbers) const;   // 发送整数数组
    void send_uniform_2(const std::string& name, const std::vector<float>& numbers) const; // 发送浮动数数组（大小为2）
    void send_uniform_2(const std::string& name, const std::vector<int>& numbers) const;   // 发送整数数组（大小为2）
    void send_uniform_3(const std::string& name, const std::vector<float>& numbers) const; // 发送浮动数数组（大小为3）
    void send_uniform_3(const std::string& name, const std::vector<int>& numbers) const;   // 发送整数数组（大小为3）
    void send_uniform_4(const std::string& name, const std::vector<float>& numbers) const; // 发送浮动数数组（大小为4）
    void send_uniform_4(const std::string& name, const std::vector<int>& numbers) const;   // 发送整数数组（大小为4）

    void send_uniform(const std::string& name, const glm::vec2& vector) const; // 发送二维向量
    void send_uniform(const std::string& name, const glm::vec3& vector) const; // 发送三维向量
    void send_uniform(const std::string& name, const Color& color) const;     // 发送颜色值

    void send_uniform(const std::string& name, const std::vector<glm::vec2>& vectors) const; // 发送二维向量数组
    void send_uniform(const std::string& name, const std::vector<glm::vec3>& vectors) const; // 发送三维向量数组
    void send_uniform(const std::string& name, const std::vector<Color>& color) const;       // 发送颜色数组

    void send_uniform(const std::string& name, const glm::mat2& matrix) const; // 发送二维矩阵
    void send_uniform(const std::string& name, const glm::mat3& matrix) const; // 发送三维矩阵
    void send_uniform(const std::string& name, const glm::mat4& matrix) const; // 发送四维矩阵

    void send_texture(const std::string& name, uint8_t texture_index) const; // 发送纹理数据

    void draw(DrawType draw_type = DrawType::Triangles) const; // 绘制顶点数据，默认绘制三角形

    bool is_valid() const;    // 判断顶点缓冲区是否有效
    void bind() const;       // 绑定顶点缓冲区
    static void unbind();    // 解绑顶点缓冲区
};

// 运算符重载，用于操作DataType枚举

DataType operator&(DataType type_1, DataType type_2); // 按位与操作
DataType operator|(DataType type_1, DataType type_2); // 按位或操作
DataType operator^(DataType type_1, DataType type_2); // 按位异或操作
DataType operator~(DataType type);                    // 按位取反操作
DataType operator<<(DataType type, uint8_t shift);    // 按位左移操作
DataType operator>>(DataType type, uint8_t shift);    // 按位右移操作

#endif

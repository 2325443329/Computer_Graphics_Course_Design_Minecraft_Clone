#include "VertexBuffer.h"

// 创建一个顶点缓冲区
VertexBuffer::VertexBuffer()
{
	shader = NULL;
	vbo = std::make_shared<GLuint>(0);
	vao = std::make_shared<GLuint>(0);
	nb_vertices = 0;
}

// 从另一个顶点缓冲区创建一个新的顶点缓冲区
VertexBuffer::VertexBuffer(const VertexBuffer& other)
{
	*this = other;
}

// 给定着色器创建一个顶点缓冲区
VertexBuffer::VertexBuffer(Shader& shader)
{
	vbo = std::make_shared<GLuint>(0);
	vao = std::make_shared<GLuint>(0);
	nb_vertices = 0;

	set_shader(shader);
}

// 创建一个顶点缓冲区并将数据发送到着色器
VertexBuffer::VertexBuffer(Shader& shader, const Mesh& mesh, DataType data_sent)
{
	send_data(shader, mesh, data_sent);
}

// 销毁顶点缓冲区
VertexBuffer::~VertexBuffer()
{
	if (vbo.unique())
	{
		glDeleteBuffers(1, &(*vbo));
		glDeleteVertexArrays(1, &(*vao));
	}
}

// 赋值操作符（注意这不是一个真正的复制操作，应该用来移动一个顶点缓冲区，而不是创建一个新的）
VertexBuffer& VertexBuffer::operator=(const VertexBuffer& other)
{
	if (vbo.unique())
	{
		glDeleteBuffers(1, &(*vbo));
		glDeleteVertexArrays(1, &(*vao));
	}

	shader = other.shader;
	vbo = other.vbo;
	vao = other.vao;
	nb_vertices = other.nb_vertices;

	return *this;
}

// 设置着色器
void VertexBuffer::set_shader(Shader& shader)
{
	this->shader = &shader;
}

// 将数据发送到着色器
void VertexBuffer::send_data(Shader& shader, const Mesh& mesh, DataType data_sent)
{
	this->shader = &shader;

	send_data(mesh, data_sent);
}

// 将数据发送到着色器
void VertexBuffer::send_data(const Mesh& mesh, DataType data_sent)
{
	if (shader == NULL)
		return;

	if (vbo.unique())
	{
		glDeleteBuffers(1, &(*vbo));
		glDeleteVertexArrays(1, &(*vao));
	}

	vbo = std::make_shared<GLuint>(0);
	vao = std::make_shared<GLuint>(0);

	bool send_positions = (data_sent & DataType::Positions) == DataType::Positions;
	bool send_normals = (data_sent & DataType::Normals) == DataType::Normals;
	bool send_texcoords = (data_sent & DataType::TexCoords) == DataType::TexCoords;

	nb_vertices = (data_sent == static_cast<DataType>(0) ? 0 : mesh.get_nb_vertices());

	if (nb_vertices)
	{
		// 创建OpenGL的顶点缓冲区

		glGenBuffers(1, &(*vbo));
		glBindBuffer(GL_ARRAY_BUFFER, *vbo);
		{
			glBufferData(GL_ARRAY_BUFFER, send_positions * mesh.get_positions_size() +
				send_normals * mesh.get_normals_size() + send_texcoords * mesh.get_texcoords_size(), NULL, GL_DYNAMIC_DRAW);

			if (send_positions)
				glBufferSubData(GL_ARRAY_BUFFER, 0, mesh.get_positions_size(), mesh.get_positions());

			if (send_normals)
				glBufferSubData(GL_ARRAY_BUFFER, send_positions * mesh.get_positions_size(), mesh.get_normals_size(), mesh.get_normals());

			if (send_texcoords)
				glBufferSubData(GL_ARRAY_BUFFER, send_positions * mesh.get_positions_size() +
					send_normals * mesh.get_normals_size(), mesh.get_texcoords_size(), mesh.get_texcoords());
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// 创建OpenGL的顶点数组

		glGenVertexArrays(1, &(*vao));
		glBindVertexArray(*vao);
		{
			glBindBuffer(GL_ARRAY_BUFFER, *vbo);
			{
				if (send_positions)
				{
					GLint positions = glGetAttribLocation(this->shader->get_id(), "a_position");
					glVertexAttribPointer(positions, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)(0));
					glEnableVertexAttribArray(positions);
				}

				if (send_normals)
				{
					GLint normals = glGetAttribLocation(this->shader->get_id(), "a_normal");
					glVertexAttribPointer(normals, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)(send_positions * mesh.get_positions_size()));
					glEnableVertexAttribArray(normals);
				}

				if (send_texcoords)
				{
					GLint texcoords = glGetAttribLocation(this->shader->get_id(), "a_texcoord");
					glVertexAttribPointer(texcoords, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)(send_positions * mesh.get_positions_size() +
						send_normals * mesh.get_normals_size()));
					glEnableVertexAttribArray(texcoords);
				}
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		glBindVertexArray(0);
	}
}

// 发送一个float到着色器
void VertexBuffer::send_uniform(const std::string& name, float number) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform1f(location, number);
}

// 发送一个int到着色器
void VertexBuffer::send_uniform(const std::string& name, int number) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform1i(location, number);
}

// 发送一个float数组到着色器
void VertexBuffer::send_uniform(const std::string& name, const std::vector<float>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform1fv(location, numbers.size(), numbers.data());
}

// 发送一个int数组到着色器
void VertexBuffer::send_uniform(const std::string& name, const std::vector<int>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform1iv(location, numbers.size(), numbers.data());
}

// 发送一个float的对数组到着色器
void VertexBuffer::send_uniform_2(const std::string& name, const std::vector<float>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform2fv(location, numbers.size() / 2, numbers.data());
}

// 发送一个int的对数组到着色器
void VertexBuffer::send_uniform_2(const std::string& name, const std::vector<int>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform2iv(location, numbers.size() / 2, numbers.data());
}

// 发送一个float的三元组数组到着色器
void VertexBuffer::send_uniform_3(const std::string& name, const std::vector<float>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform3fv(location, numbers.size() / 3, numbers.data());
}

// 发送一个int的三元组数组到着色器
void VertexBuffer::send_uniform_3(const std::string& name, const std::vector<int>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform3iv(location, numbers.size() / 3, numbers.data());
}

// 发送一个float的四元组数组到着色器
void VertexBuffer::send_uniform_4(const std::string& name, const std::vector<float>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform4fv(location, numbers.size() / 4, numbers.data());
}

// 发送一个int的四元组数组到着色器
void VertexBuffer::send_uniform_4(const std::string& name, const std::vector<int>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform4iv(location, numbers.size() / 4, numbers.data());
}

// 发送一个2D向量到着色器
void VertexBuffer::send_uniform(const std::string& name, const glm::vec2& vector) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform2f(location, vector.x, vector.y);
}

// 发送一个3D向量到着色器
void VertexBuffer::send_uniform(const std::string& name, const glm::vec3& vector) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform3f(location, vector.x, vector.y, vector.z);
}

// 发送一个颜色到着色器
void VertexBuffer::send_uniform(const std::string& name, const Color& color) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform4f(location, color.r, color.g, color.b, color.a);
}

// 发送一个2D向量数组到着色器
void VertexBuffer::send_uniform(const std::string& name, const std::vector<glm::vec2>& vectors) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform2fv(location, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
}

// 发送一个3D向量数组到着色器
void VertexBuffer::send_uniform(const std::string& name, const std::vector<glm::vec3>& vectors) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform3fv(location, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
}

// 发送一个4D向量数组到着色器
void VertexBuffer::send_uniform(const std::string& name, const std::vector<Color>& vectors) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform4fv(location, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
}

// 发送一个2x2矩阵到着色器
void VertexBuffer::send_uniform(const std::string& name, const glm::mat2& matrix) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

// 发送一个3x3矩阵到着色器
void VertexBuffer::send_uniform(const std::string& name, const glm::mat3& matrix) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

// 发送一个4x4矩阵到着色器
void VertexBuffer::send_uniform(const std::string& name, const glm::mat4& matrix) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

// 发送一个纹理到着色器
void VertexBuffer::send_texture(const std::string& name, uint8_t texture_index) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform1i(location, texture_index);
}

// 绘制顶点缓冲区
void VertexBuffer::draw(DrawType draw_type) const
{
	if (nb_vertices)
		glDrawArrays((GLenum)draw_type, 0, nb_vertices);
}

// 验证顶点缓冲区是否可用
bool VertexBuffer::is_valid() const
{
	return shader != NULL && *vbo != 0 && *vao != 0;
}

// 绑定顶点缓冲区
void VertexBuffer::bind() const
{
	glBindVertexArray(*vao);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
}

// 解除绑定顶点缓冲区
void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// AND 操作符
DataType operator&(DataType type_1, DataType type_2)
{
	return static_cast<DataType>(static_cast<uint8_t>(type_1) & static_cast<uint8_t>(type_2));
}

// OR 操作符
DataType operator|(DataType type_1, DataType type_2)
{
	return static_cast<DataType>(static_cast<uint8_t>(type_1) | static_cast<uint8_t>(type_2));
}

// XOR 操作符
DataType operator^(DataType type_1, DataType type_2)
{
	return static_cast<DataType>(static_cast<uint8_t>(type_1) ^ static_cast<uint8_t>(type_2));
}

// NOT 操作符
DataType operator~(DataType type)
{
	return static_cast<DataType>(~static_cast<uint8_t>(type));
}

// 左移操作符
DataType operator<<(DataType type, uint8_t shift)
{
	return static_cast<DataType>(static_cast<uint8_t>(type) << shift);
}

// 右移操作符
DataType operator>>(DataType type, uint8_t shift)
{
	return static_cast<DataType>(static_cast<uint8_t>(type) >> shift);
}

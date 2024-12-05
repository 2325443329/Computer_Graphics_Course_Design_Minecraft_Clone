#include "VertexBuffer.h"

// ����һ�����㻺����
VertexBuffer::VertexBuffer()
{
	shader = NULL;
	vbo = std::make_shared<GLuint>(0);
	vao = std::make_shared<GLuint>(0);
	nb_vertices = 0;
}

// ����һ�����㻺��������һ���µĶ��㻺����
VertexBuffer::VertexBuffer(const VertexBuffer& other)
{
	*this = other;
}

// ������ɫ������һ�����㻺����
VertexBuffer::VertexBuffer(Shader& shader)
{
	vbo = std::make_shared<GLuint>(0);
	vao = std::make_shared<GLuint>(0);
	nb_vertices = 0;

	set_shader(shader);
}

// ����һ�����㻺�����������ݷ��͵���ɫ��
VertexBuffer::VertexBuffer(Shader& shader, const Mesh& mesh, DataType data_sent)
{
	send_data(shader, mesh, data_sent);
}

// ���ٶ��㻺����
VertexBuffer::~VertexBuffer()
{
	if (vbo.unique())
	{
		glDeleteBuffers(1, &(*vbo));
		glDeleteVertexArrays(1, &(*vao));
	}
}

// ��ֵ��������ע���ⲻ��һ�������ĸ��Ʋ�����Ӧ�������ƶ�һ�����㻺�����������Ǵ���һ���µģ�
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

// ������ɫ��
void VertexBuffer::set_shader(Shader& shader)
{
	this->shader = &shader;
}

// �����ݷ��͵���ɫ��
void VertexBuffer::send_data(Shader& shader, const Mesh& mesh, DataType data_sent)
{
	this->shader = &shader;

	send_data(mesh, data_sent);
}

// �����ݷ��͵���ɫ��
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
		// ����OpenGL�Ķ��㻺����

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

		// ����OpenGL�Ķ�������

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

// ����һ��float����ɫ��
void VertexBuffer::send_uniform(const std::string& name, float number) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform1f(location, number);
}

// ����һ��int����ɫ��
void VertexBuffer::send_uniform(const std::string& name, int number) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform1i(location, number);
}

// ����һ��float���鵽��ɫ��
void VertexBuffer::send_uniform(const std::string& name, const std::vector<float>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform1fv(location, numbers.size(), numbers.data());
}

// ����һ��int���鵽��ɫ��
void VertexBuffer::send_uniform(const std::string& name, const std::vector<int>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform1iv(location, numbers.size(), numbers.data());
}

// ����һ��float�Ķ����鵽��ɫ��
void VertexBuffer::send_uniform_2(const std::string& name, const std::vector<float>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform2fv(location, numbers.size() / 2, numbers.data());
}

// ����һ��int�Ķ����鵽��ɫ��
void VertexBuffer::send_uniform_2(const std::string& name, const std::vector<int>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform2iv(location, numbers.size() / 2, numbers.data());
}

// ����һ��float����Ԫ�����鵽��ɫ��
void VertexBuffer::send_uniform_3(const std::string& name, const std::vector<float>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform3fv(location, numbers.size() / 3, numbers.data());
}

// ����һ��int����Ԫ�����鵽��ɫ��
void VertexBuffer::send_uniform_3(const std::string& name, const std::vector<int>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform3iv(location, numbers.size() / 3, numbers.data());
}

// ����һ��float����Ԫ�����鵽��ɫ��
void VertexBuffer::send_uniform_4(const std::string& name, const std::vector<float>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform4fv(location, numbers.size() / 4, numbers.data());
}

// ����һ��int����Ԫ�����鵽��ɫ��
void VertexBuffer::send_uniform_4(const std::string& name, const std::vector<int>& numbers) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform4iv(location, numbers.size() / 4, numbers.data());
}

// ����һ��2D��������ɫ��
void VertexBuffer::send_uniform(const std::string& name, const glm::vec2& vector) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform2f(location, vector.x, vector.y);
}

// ����һ��3D��������ɫ��
void VertexBuffer::send_uniform(const std::string& name, const glm::vec3& vector) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform3f(location, vector.x, vector.y, vector.z);
}

// ����һ����ɫ����ɫ��
void VertexBuffer::send_uniform(const std::string& name, const Color& color) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform4f(location, color.r, color.g, color.b, color.a);
}

// ����һ��2D�������鵽��ɫ��
void VertexBuffer::send_uniform(const std::string& name, const std::vector<glm::vec2>& vectors) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform2fv(location, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
}

// ����һ��3D�������鵽��ɫ��
void VertexBuffer::send_uniform(const std::string& name, const std::vector<glm::vec3>& vectors) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform3fv(location, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
}

// ����һ��4D�������鵽��ɫ��
void VertexBuffer::send_uniform(const std::string& name, const std::vector<Color>& vectors) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform4fv(location, vectors.size(), reinterpret_cast<const float*>(vectors.data()));
}

// ����һ��2x2������ɫ��
void VertexBuffer::send_uniform(const std::string& name, const glm::mat2& matrix) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

// ����һ��3x3������ɫ��
void VertexBuffer::send_uniform(const std::string& name, const glm::mat3& matrix) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

// ����һ��4x4������ɫ��
void VertexBuffer::send_uniform(const std::string& name, const glm::mat4& matrix) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

// ����һ��������ɫ��
void VertexBuffer::send_texture(const std::string& name, uint8_t texture_index) const
{
	GLint location = glGetUniformLocation(shader->get_id(), name.data());
	glUniform1i(location, texture_index);
}

// ���ƶ��㻺����
void VertexBuffer::draw(DrawType draw_type) const
{
	if (nb_vertices)
		glDrawArrays((GLenum)draw_type, 0, nb_vertices);
}

// ��֤���㻺�����Ƿ����
bool VertexBuffer::is_valid() const
{
	return shader != NULL && *vbo != 0 && *vao != 0;
}

// �󶨶��㻺����
void VertexBuffer::bind() const
{
	glBindVertexArray(*vao);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
}

// ����󶨶��㻺����
void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// AND ������
DataType operator&(DataType type_1, DataType type_2)
{
	return static_cast<DataType>(static_cast<uint8_t>(type_1) & static_cast<uint8_t>(type_2));
}

// OR ������
DataType operator|(DataType type_1, DataType type_2)
{
	return static_cast<DataType>(static_cast<uint8_t>(type_1) | static_cast<uint8_t>(type_2));
}

// XOR ������
DataType operator^(DataType type_1, DataType type_2)
{
	return static_cast<DataType>(static_cast<uint8_t>(type_1) ^ static_cast<uint8_t>(type_2));
}

// NOT ������
DataType operator~(DataType type)
{
	return static_cast<DataType>(~static_cast<uint8_t>(type));
}

// ���Ʋ�����
DataType operator<<(DataType type, uint8_t shift)
{
	return static_cast<DataType>(static_cast<uint8_t>(type) << shift);
}

// ���Ʋ�����
DataType operator>>(DataType type, uint8_t shift)
{
	return static_cast<DataType>(static_cast<uint8_t>(type) >> shift);
}

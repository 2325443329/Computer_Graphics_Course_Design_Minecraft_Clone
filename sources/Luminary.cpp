#include "Luminary.h"
#include "Game.h"
#include "Mesh.h"
#include "Shader.h"

const glm::mat4	Luminary::scale_matrix = glm::scale(glm::mat4(1.f), glm::vec3(size, size, size));
const glm::mat4	Luminary::translation_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -distance));
const glm::mat4	Luminary::rotation_matrix = glm::rotate(glm::mat4(1.f), angle, glm::vec3(0.f, 1.f, 0.f));

// 创建一个天体

Luminary::Luminary()
{
	texture = NULL;
	model = glm::mat4(1.f);
}

// 从另一个天体创建一个天体

Luminary::Luminary(const Luminary& other)
{
	*this = other;
}

// 重载赋值操作符

Luminary& Luminary::operator=(const Luminary& other)
{
	texture = other.texture;
	light = other.light;
	model = other.model;
	object = other.object;

	return *this;
}

// 初始化天体

void Luminary::init()
{
	// 设置光源类型为定向光，光强度为1
	this->light.set_type(Light::Type::Directional);
	this->light.set_intensity(1.f);

	// 发送顶点数据给着色器
	object.send_data(Shader::luminary, Mesh::square, DataType::Positions | DataType::TexCoords);
}

// 绘制天体

void Luminary::draw(const Camera& camera, const std::vector<const Light*>& lights) const
{
	Shader::luminary.bind();
	texture->bind(0); // 绑定纹理
	object.bind();

	// 发送矩阵和其他参数给着色器
	object.send_uniform("u_model", model);
	object.send_uniform("u_mvp", camera.get_matrix() * model);
	object.send_uniform("u_camera", camera.get_position());
	object.send_uniform("u_water_level", water_level);
	object.send_uniform("u_fake_cam", (int)Game::fake_cam);

	ColorRGB water_color = ColorRGB(0.f, 0.f, 0.f);

	// 计算水面颜色，结合所有光源的颜色和强度
	for (uint16_t i = 0; i < std::min((int)lights.size(), (int)nb_max_lights); i++)
		water_color += ColorRGB(Material::water.get_color()) * ColorRGB(lights[i]->get_color()) * lights[i]->get_intensity();

	// 发送水面颜色到着色器
	object.send_uniform("u_water_color", water_color);
	object.send_texture("u_texture", 0); // 绑定纹理
	object.draw(); // 绘制天体

	VertexBuffer::unbind(); // 解绑顶点缓冲区
	Texture::unbind(); // 解绑纹理
	Shader::unbind(); // 解绑着色器
}

// 获取天体的位置

glm::vec3 Luminary::get_position() const
{
	return model * glm::vec3(0.f, 0.f, 0.f);
}

// 获取天体的光源指针

const Light* Luminary::get_light() const
{
	return &light;
}

#include "Texture.h"
#include <sstream>

Texture Texture::blocks;
std::vector<Texture> Texture::player_skins;
Texture Texture::sun;
Texture Texture::moon;
Texture Texture::water_dudv;
Texture Texture::water_normals;
Texture Texture::cursor;
Texture Texture::wolf;
Texture Texture::fox;
Texture Texture::chicken;

// 初始化一个纹理
Texture::Texture()
{
	id = std::make_shared<GLuint>(0);
}

// 从另一个纹理创建一个纹理
Texture::Texture(const Texture& other)
{
	*this = other;
}

// 从图片创建一个纹理
Texture::Texture(const std::string& path)
{
	load(path);
}

// 销毁一个纹理
Texture::~Texture()
{
	if (id.unique())
		glDeleteTextures(1, &(*id));
}

// 赋值操作符 (注意这不是一个真正的复制，使用时应当移动纹理而不是创建新的纹理)
Texture& Texture::operator=(const Texture& other)
{
	if (id.unique())
		glDeleteTextures(1, &(*id));

	id = other.id;

	return *this;
}

// 将图片应用到纹理上
void Texture::load(const std::string& path, GLenum wrapping, GLint filtering)
{
	if (id.unique())
		glDeleteTextures(1, &(*id));

	id = std::make_shared<GLuint>(0);
	SDL_Surface* image = IMG_Load(path.data());
	SDL_Surface* rgba_image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA32, 0);

	glGenTextures(1, &(*id));
	glBindTexture(GL_TEXTURE_2D, *id);
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, rgba_image->w, rgba_image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)rgba_image->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(image);
	SDL_FreeSurface(rgba_image);
}

// 绑定纹理
void Texture::bind(uint8_t index) const
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, *id);
}

// 获取纹理的 id
GLuint Texture::get_id() const
{
	return *id;
}

// 获取纹理 id 的指针
GLuint* Texture::get_id_ptr()
{
	return &(*id);
}

// 更改纹理的 id
void Texture::set_id(GLuint id)
{
	*(this->id) = id;
}

// 解除绑定纹理
void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load_player_skins() {
	player_skins.clear();

	// 假设皮肤文件名是从 0.png 开始
	const int max_skins = 10000;  // 假设最多有 10000 个皮肤
	for (int i = 0; i < max_skins; i++) {
		std::string filename = "textures/player/" + std::to_string(i) + ".png";

		// 尝试加载该文件，如果文件不存在，则跳出循环
		if (SDL_RWFromFile(filename.c_str(), "r") == nullptr) {
			break;  // 如果文件不存在，跳出循环
		}

		// 加载纹理
		player_skins.push_back(Texture(filename));
	}
}

// 初始化程序中使用的纹理
void Texture::init()
{
	Texture::blocks.load("textures/textures.png");
	Texture::load_player_skins();
	Texture::sun.load("textures/sun.png");
	Texture::moon.load("textures/moon.png");
	Texture::water_dudv.load("textures/water_dudv.png", GL_MIRRORED_REPEAT, GL_LINEAR);
	Texture::water_normals.load("textures/water_normals.png", GL_REPEAT, GL_LINEAR);
	Texture::cursor.load("textures/cursor.png");
	Texture::chicken.load("textures/chicken.png");
	Texture::wolf.load("textures/wolf.png");
	Texture::fox.load("textures/fox.png");
}

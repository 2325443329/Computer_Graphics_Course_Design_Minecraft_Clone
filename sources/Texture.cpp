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

// ��ʼ��һ������
Texture::Texture()
{
	id = std::make_shared<GLuint>(0);
}

// ����һ��������һ������
Texture::Texture(const Texture& other)
{
	*this = other;
}

// ��ͼƬ����һ������
Texture::Texture(const std::string& path)
{
	load(path);
}

// ����һ������
Texture::~Texture()
{
	if (id.unique())
		glDeleteTextures(1, &(*id));
}

// ��ֵ������ (ע���ⲻ��һ�������ĸ��ƣ�ʹ��ʱӦ���ƶ���������Ǵ����µ�����)
Texture& Texture::operator=(const Texture& other)
{
	if (id.unique())
		glDeleteTextures(1, &(*id));

	id = other.id;

	return *this;
}

// ��ͼƬӦ�õ�������
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

// ������
void Texture::bind(uint8_t index) const
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, *id);
}

// ��ȡ����� id
GLuint Texture::get_id() const
{
	return *id;
}

// ��ȡ���� id ��ָ��
GLuint* Texture::get_id_ptr()
{
	return &(*id);
}

// ��������� id
void Texture::set_id(GLuint id)
{
	*(this->id) = id;
}

// ���������
void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load_player_skins() {
	player_skins.clear();

	// ����Ƥ���ļ����Ǵ� 0.png ��ʼ
	const int max_skins = 10000;  // ��������� 10000 ��Ƥ��
	for (int i = 0; i < max_skins; i++) {
		std::string filename = "textures/player/" + std::to_string(i) + ".png";

		// ���Լ��ظ��ļ�������ļ������ڣ�������ѭ��
		if (SDL_RWFromFile(filename.c_str(), "r") == nullptr) {
			break;  // ����ļ������ڣ�����ѭ��
		}

		// ��������
		player_skins.push_back(Texture(filename));
	}
}

// ��ʼ��������ʹ�õ�����
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

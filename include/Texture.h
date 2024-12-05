#ifndef TEXTURE_H
#define TEXTURE_H

#include "utils.h"

// 定义纹理类，用于管理和操作纹理

class Texture
{
private:

	std::shared_ptr<GLuint>	id;				// 纹理ID，用于OpenGL中的纹理对象

public:

	static Texture			blocks;			// 方块的纹理
	//static Texture			player;			// 玩家模型的纹理
	static Texture			sun;			// 太阳的纹理
	static Texture			moon;			// 月亮的纹理
	static Texture			water_dudv;		// 用于扭曲水面反射的纹理
	static Texture			water_normals;	// 代表水面法线的纹理
	static Texture			cursor;			// 游戏中的光标纹理
	static Texture          wolf;            // 狼的纹理
	static Texture          fox;             // 狐狸的纹理
	static Texture          chicken;         // 鸡的纹理
	static std::vector<Texture> player_skins; // 用于存储所有玩家皮肤纹理

	Texture();				// 构造函数
	Texture(const Texture& other);	// 复制构造函数
	Texture(const std::string& path);	// 带路径的构造函数
	~Texture();				// 析构函数

	Texture& operator=(const Texture& other);	// 赋值运算符

	// 加载纹理，支持纹理包裹模式和过滤模式的设置
	void					load(const std::string& path, GLenum wrapping = GL_REPEAT, GLint filtering = GL_NEAREST);

	// 绑定纹理到指定的纹理单元
	void					bind(uint8_t index) const;

	// 获取纹理的ID
	GLuint					get_id() const;

	// 获取纹理ID的指针
	GLuint* get_id_ptr();

	// 设置纹理的ID
	void					set_id(GLuint id);

	// 解绑纹理
	static void				unbind();

	// 初始化纹理管理（例如，设置纹理的默认状态）
	static void				init();

	// 用于加载所有的玩家皮肤纹理
	static void load_player_skins();
};

#endif

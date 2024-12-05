#ifndef SHADER_H
#define SHADER_H

#include "libraries.h"

// 错误和日志消息的最大长度定义
#define ERROR_MAX_LENGTH 500

// 颜色控制宏，用于格式化日志输出
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define BOLD  "\x1B[1m"
#define RESET "\x1B[0m"

// 位操作宏，用于设置和清除特定位
#define SET_BIT(bits, pos)   (bits |= 1 << (pos))
#define RESET_BIT(bits, pos) (bits &= ~(1 << (pos)))

// 获取当前文件的文件名（去除路径）
#ifndef __FILENAME__
#define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)
#endif

// 定义错误、警告和信息输出的宏，带有文件名和行号
#ifndef SHADER_ERROR
#define SHADER_ERROR(x, ...)     (fprintf(stderr, RED "Error : " GRN "%s:%d " RESET x, __FILENAME__, __LINE__, ## __VA_ARGS__))
#endif

#ifndef SHADER_WARNING
#define SHADER_WARNING(x, ...)   (fprintf(stdout, YEL "Warning : " GRN "%s:%d " RESET x, __FILENAME__, __LINE__, ## __VA_ARGS__))
#endif

#ifndef SHADER_INFO
#define SHADER_INFO(x, ...)   (fprintf(stdout, BOLD WHT "INFO : " RESET GRN "%s:%d " RESET x , __FILENAME__, __LINE__, ## __VA_ARGS__))
#endif

// 这里没有直接使用 std::cout，而是用宏来格式化错误、警告和信息

// Shader类，用于加载和管理着色器程序
class Shader
{
private:

	std::shared_ptr<GLuint>	program_id;	// 着色器程序ID
	std::shared_ptr<GLuint>	vertex_id;	// 顶点着色器ID
	std::shared_ptr<GLuint>	frag_id;	// 片段着色器ID

	// 加载着色器代码
	int						loadShader(const std::string& code, int type);

	// 从文件加载着色器
	bool					loadFromFiles(FILE* vertexFile, FILE* fragFile);

	// 从字符串加载着色器
	bool					loadFromStrings(const std::string& vertexString, const std::string& fragString);

public:

	// 各种预定义的着色器（例如，水、天空、块、光晕等）
	static Shader			block;		// 块的着色器
	static Shader			entity;		// 实体（例如怪物）的着色器
	static Shader			sky;		// 天空的着色器
	static Shader			luminary;	// 天体的着色器
	static Shader			water;		// 水面的着色器
	static Shader			in_water;	// 玩家在水下时的水面着色器
	static Shader			screen;		// 后处理的着色器
	static Shader			lens_flare;	// 镜头光晕的着色器
	static Shader			debug;		// 调试着色器

	// 构造函数和析构函数
	Shader();
	Shader(const Shader& other);
	Shader(const std::string& vert_path, const std::string& frag_path);
	~Shader();

	Shader& operator=(const Shader& other);

	// 从文件加载着色器
	bool					load(const std::string& vert_path, const std::string& frag_path);

	// 获取着色器程序ID
	GLuint					get_id() const;

	// 绑定着色器
	void					bind() const;

	// 解除绑定着色器
	static void				unbind();

	// 初始化着色器系统
	static void				init();
};

#endif

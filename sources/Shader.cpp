#include "Shader.h"

Shader Shader::block;
Shader Shader::entity;
Shader Shader::sky;
Shader Shader::luminary;
Shader Shader::water;
Shader Shader::in_water;
Shader Shader::screen;
Shader Shader::lens_flare;
Shader Shader::debug;

// 我不知道，这不是我的函数
int Shader::loadShader(const std::string& code, int type)
{
	int shader = glCreateShader(type);
	const GLchar* s = code.c_str();
	glShaderSource(shader, 1, &s, 0);
	glCompileShader(shader);

	int compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (compiled == GL_FALSE)
	{
		char* error = (char*)malloc(ERROR_MAX_LENGTH * sizeof(char)); // 这里内存泄漏 :(
		int length = 0;
		glGetShaderInfoLog(shader, ERROR_MAX_LENGTH, &length, error);

		SHADER_ERROR("无法编译着色器 %d : \n %s", type, error);
		glDeleteShader(shader);

		// free(error) ?

		return 0;
	}

	return shader;
}

// 我也不知道...
bool Shader::loadFromFiles(FILE* vertexFile, FILE* fragFile)
{
	uint32_t vertexFileSize = 0;
	uint32_t fragFileSize = 0;
	char* vertexCodeC;
	char* fragCodeC;

	fseek(vertexFile, 0, SEEK_END);
	vertexFileSize = ftell(vertexFile);
	fseek(vertexFile, 0, SEEK_SET);

	fseek(fragFile, 0, SEEK_END);
	fragFileSize = ftell(fragFile);
	fseek(fragFile, 0, SEEK_SET);

	vertexCodeC = (char*)malloc(vertexFileSize + 1);
	fragCodeC = (char*)malloc(fragFileSize + 1);

	fread(vertexCodeC, 1, vertexFileSize, vertexFile);
	vertexCodeC[vertexFileSize] = '\0';
	fread(fragCodeC, 1, fragFileSize, fragFile);
	fragCodeC[fragFileSize] = '\0';

	bool result = loadFromStrings(std::string(vertexCodeC), std::string(fragCodeC));

	free(vertexCodeC);
	free(fragCodeC);

	return result;
}

// 神秘的...
bool Shader::loadFromStrings(const std::string& vertexString, const std::string& fragString)
{
	*program_id = glCreateProgram();
	*vertex_id = loadShader(vertexString, GL_VERTEX_SHADER);
	*frag_id = loadShader(fragString, GL_FRAGMENT_SHADER);

	glAttachShader(*program_id, *vertex_id);
	glAttachShader(*program_id, *frag_id);

	glLinkProgram(*program_id);

	int linkStatus;
	glGetProgramiv(*program_id, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE)
	{
		char* error = (char*)malloc(ERROR_MAX_LENGTH * sizeof(char)); // 还是内存泄漏 :(
		int length = 0;
		glGetProgramInfoLog(*program_id, ERROR_MAX_LENGTH, &length, error);
		SHADER_ERROR("无法链接着色器-> : \n %s", error);

		// free(error) ?

		return false;
	}

	return true;
}


// 创建一个shader
Shader::Shader()
{
	program_id = std::make_shared<GLuint>(0);
	vertex_id = std::make_shared<GLuint>(0);
	frag_id = std::make_shared<GLuint>(0);
}

// 从另一个shader创建一个shader
Shader::Shader(const Shader& other)
{
	*this = other;
}

// 从文件创建一个shader
Shader::Shader(const std::string& vert_path, const std::string& frag_path)
{
	load(vert_path, frag_path);
}

// 销毁shader
Shader::~Shader()
{
	if (program_id.unique())
	{
		glDeleteProgram(*program_id);
		glDeleteShader(*vertex_id);
		glDeleteShader(*frag_id);
	}
}

// 赋值操作符（注意这不是一个真正的拷贝，应该用于替换shader，而不是创建一个新的shader）
Shader& Shader::operator=(const Shader& other)
{
	if (program_id.unique())
	{
		glDeleteProgram(*program_id);
		glDeleteShader(*vertex_id);
		glDeleteShader(*frag_id);
	}

	program_id = other.program_id;
	vertex_id = other.vertex_id;
	frag_id = other.frag_id;

	return *this;
}

// 从文件打开并编译shader
bool Shader::load(const std::string& vert_path, const std::string& frag_path)
{
	if (program_id.unique())
	{
		glDeleteProgram(*program_id);
		glDeleteShader(*vertex_id);
		glDeleteShader(*frag_id);
	}

	program_id = std::make_shared<GLuint>(0);
	vertex_id = std::make_shared<GLuint>(0);
	frag_id = std::make_shared<GLuint>(0);

	FILE* vertFile = fopen(vert_path.data(), "r");
	FILE* fragFile = fopen(frag_path.data(), "r");

	bool result = loadFromFiles(vertFile, fragFile);

	fclose(vertFile);
	fclose(fragFile);

	return result;
}

// 获取程序的id
GLuint Shader::get_id() const
{
	return *program_id;
}

// 绑定shader
void Shader::bind() const
{
	glUseProgram(get_id());
}

// 解绑shader
void Shader::unbind()
{
	glUseProgram(0);
}

// 打开程序中使用的着色器
void Shader::init()
{
	Shader::block.load("shaders/block.vert", "shaders/block.frag");
	Shader::entity.load("shaders/entity.vert", "shaders/entity.frag");
	Shader::sky.load("shaders/sky.vert", "shaders/sky.frag");
	Shader::luminary.load("shaders/luminary.vert", "shaders/luminary.frag");
	Shader::water.load("shaders/water.vert", "shaders/water.frag");
	Shader::in_water.load("shaders/in_water.vert", "shaders/in_water.frag");
	Shader::screen.load("shaders/screen.vert", "shaders/screen.frag");
	Shader::lens_flare.load("shaders/lens_flare.vert", "shaders/lens_flare.frag");
	Shader::debug.load("shaders/debug.vert", "shaders/debug.frag");
}

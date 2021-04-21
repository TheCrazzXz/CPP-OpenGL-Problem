#include "Shader.h"

Shader::Shader()
{

}
Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	generate(vertexShaderPath, fragmentShaderPath);
}

void Shader::generate(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	int success;
	char infoLog[1024];

	GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 1024, NULL, infoLog);
		std::cerr << "Error : At shader compilation : " << std::endl << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
void Shader::activate()
{
	glUseProgram(id);
}
std::string Shader::loadShaderSrc(const char* filename)
{
	std::ifstream file;
	std::stringstream buf;

	std::string output = ""; //Return

	file.open(filename);

	if (file.is_open())
	{
		buf << file.rdbuf();
		output = buf.str();
	}
	else
	{
		std::cerr << "Error : Failed to open the file '" << filename << "'" << std::endl;
	}
	file.close();
	return output;
}
GLuint Shader::compileShader(const char* filepath, GLenum type)
{
	int success;
	char infoLog[1024];

	GLuint output = glCreateShader(type);
	std::string shaderSrc = loadShaderSrc(filepath);
	const GLchar* shader = shaderSrc.c_str();
	glShaderSource(output, 1, &shader, NULL);
	glCompileShader(output);
	glGetShaderiv(output, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(output, 1024, NULL, infoLog);
		std::cerr << "Error : At fragment shader compilation : " << std::endl << infoLog << std::endl;
	}

	return output;
}
void Shader::setMat4(const std::string & name, glm::mat4 val)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}
void Shader::setBool(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set3Float(const std::string& name, float v1, float v2, float v3) {
	glUniform3f(glGetUniformLocation(id, name.c_str()), v1, v2, v3);
}

void Shader::set3Float(const std::string& name, glm::vec3 v) {
	glUniform3f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z);
}

void Shader::set4Float(const std::string& name, float v1, float v2, float v3, float v4) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), v1, v2, v3, v4);
}

void Shader::set4Float(const std::string& name, glm::vec4 v) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z, v.w);
}

void Shader::setMat3(const std::string& name, glm::mat3 val) {
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}
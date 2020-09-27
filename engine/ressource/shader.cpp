#include "shader.h"

Shader::Shader()
{

}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

/*
	loading shader
*/

void Shader::load(const std::string&& vertexFile, const std::string&& fragmentFile)
{
	m_program = glCreateProgram();

	load_vertex(std::move(vertexFile));
	load_fragment(std::move(fragmentFile));

	glLinkProgram(m_program);
	check_link();

	glDeleteShader(m_vertex);
	glDeleteShader(m_fragment);
}

void Shader::load_vertex(const std::string&& filename)
{
	m_vertex = glCreateShader(GL_VERTEX_SHADER);
	
	std::string vertexSource;
	read_from_file(("../ressource/shader/" + filename).c_str(), vertexSource);
	compile_shader(vertexSource.c_str(), m_vertex, "vertex");

	glAttachShader(m_program, m_vertex);
}

void Shader::load_fragment(const std::string&& filename)
{
	m_fragment = glCreateShader(GL_FRAGMENT_SHADER);

	std::string fragmentSource;
	read_from_file(("../ressource/shader/" + filename).c_str(), fragmentSource);
	compile_shader(fragmentSource.c_str(), m_fragment, "fragment");

	glAttachShader(m_program, m_fragment);
}

/*
	bind
*/

void Shader::bind()
{
	glUseProgram(m_program);
}

/*
	compile and check problem
*/

void Shader::compile_shader(const char* source, GLuint shader, const char*&& name)
{
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;
	char info[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, info);
		throw std::runtime_error(std::string("shader compilation error [") + name + "]: " + info);
	}
}

void Shader::check_link()
{
	int success;
	char info[512];
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(m_program, 512, NULL, info);
		throw std::runtime_error(std::string("shader compilation error [program]: ") + info);
	}
}

/*
	read from file
*/

void Shader::read_from_file(const char* filename, std::string& source)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error(std::string("error: can't open shader file [") + filename + "].");
	}

	std::string line;
	while (getline(file, line)) {
		source += line + '\n';
	}

	file.close();
}

/*
	uniform
*/

GLuint Shader::uniform_loc(const char* name) {
	return glGetUniformLocation(m_program, name);
}

void Shader::set_mat4(const char*&& name, const glm::mat4& value) {
	glUniformMatrix4fv(uniform_loc(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_vec4(const char*&& name, const glm::vec4& value) {
	glUniform4f(uniform_loc(name), value.x, value.y, value.z, value.w);
}

void Shader::set_vec3(const char*&& name, const glm::vec3& value) {
	glUniform3f(uniform_loc(name), value.x, value.y, value.z);
}

void Shader::set_bool(const char*&& name, bool value) {
	glUniform1i(uniform_loc(name), value);
}

void Shader::set_int(const char*&& name, int value) {
	glUniform1i(uniform_loc(name), value);
}

void Shader::set_float(const char*&& name, float value) {
	glUniform1f(uniform_loc(name), value);
}



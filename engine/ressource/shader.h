#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader();
	~Shader();

	void load(const std::string&& vertexFile, const std::string&& fragmentFile);
	void bind();

	void set_mat4(const char*&& name, const glm::mat4& value);
	void set_vec4(const char*&& name, const glm::vec4& value);
	void set_vec3(const char*&& name, const glm::vec3& value);
	void set_bool(const char*&& name, bool value);
	void set_int(const char*&& name, int value);
	void set_float(const char*&& name, float value);
	
private:
	GLuint m_program;
	GLuint m_vertex;
	GLuint m_fragment;

	void load_vertex(const std::string&& filename);
	void load_fragment(const std::string&& filename);

	//first time using rvalue
	void compile_shader(const char* source, GLuint shader, const char*&& name); 
	void read_from_file(const char* filename, std::string& source);
	void check_link();
	GLuint uniform_loc(const char* name);
};

#endif //SHADER_H
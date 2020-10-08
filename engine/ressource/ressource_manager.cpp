#include "ressource_manager.h"

RessourceManager::RessourceManager()
{

}

RessourceManager::~RessourceManager()
{
	//meshes
	auto mesh = m_meshManager.begin();
	while (mesh != m_meshManager.end()) {
		delete_mesh(mesh->first, mesh->second);
		mesh++;
	}

	//shader
	auto shader = m_shaderManager.begin();
	while(shader != m_shaderManager.end()) {
		delete_shader(shader->first, shader->second);
		shader++;
	}

	//textures
	auto tex = m_textureManager.begin();
	while (tex != m_textureManager.end()) {
		delete_texture(tex->first, tex->second);
		tex++;
	}
}

/*
	mesh
*/

Mesh* RessourceManager::load_mesh(const std::string&& name, const std::string&& filename)
{
	auto it = m_meshManager.find(name);
	
	if (it != m_meshManager.end()) {
		throw std::runtime_error("error: mesh already exist [" + name + "] [" + filename + "]");
	}

	std::cout << "mesh: loaded [" << name << "] at [" << filename << "]" << std::endl;

	Mesh* mesh = new Mesh();
	mesh->load(std::move(filename));
	m_meshManager.emplace(name, mesh);
	return mesh;
}

Mesh* RessourceManager::get_mesh(const std::string&& name)
{
	auto it = m_meshManager.find(name);

	if (it == m_meshManager.end()) {
		throw std::runtime_error("error: mesh doesn't exist [" + name + "]");
	}

	return it->second;
}

void RessourceManager::remove_mesh(const std::string&& name)
{
	auto it = m_meshManager.find(name);

	if (it == m_meshManager.end()) {
		throw std::runtime_error("error: mesh doesn't exist [" + name + "]");
	}

	delete_mesh(name, it->second);
	m_meshManager.erase(it);
}

void RessourceManager::delete_mesh(const std::string name, Mesh* mesh)
{
	std::cout << "mesh: deleted [" << name << "]" << std::endl;
	delete mesh;
}

/*
	shader
*/

Shader* RessourceManager::load_shader(const std::string&& name, const std::string&& vertexFile, const std::string&& fragmentFile)
{
	auto it = m_shaderManager.find(name);

	if (it != m_shaderManager.end())
		throw std::runtime_error("error: shader already exist [" + name + "] [" + vertexFile + "] [" + fragmentFile + "]");

	std::cout << "shader: loaded [" << name << "] at [" << vertexFile << "] [" << fragmentFile << "]" << std::endl;

	Shader* shader = new Shader();
	shader->load(std::move(vertexFile), std::move(fragmentFile));
	m_shaderManager.emplace(name, shader);
	return shader;
}

Shader* RessourceManager::get_shader(const std::string&& name)
{
	auto it = m_shaderManager.find(name);

	if (it == m_shaderManager.end())
		throw std::runtime_error("error: shader doesn't exist [" + name + "]");

	return it->second;
}

void RessourceManager::remove_shader(const std::string&& name)
{
	auto it = m_shaderManager.find(name);

	if (it == m_shaderManager.end())
		throw std::runtime_error("error: shader doesn't exist [" + name + "]");

	delete_shader(name, it->second);
	m_shaderManager.erase(it);
}

void RessourceManager::delete_shader(const std::string name, Shader* shader)
{
	std::cout << "shader: deleted [" << name << "]" << std::endl;
	delete shader;
}

/*
	texture
*/

Texture* RessourceManager::load_texture(const std::string&& name, const std::string&& filename)
{
	auto it = m_textureManager.find(name);

	if (it != m_textureManager.end())
		throw std::runtime_error("error: texture already exist [" + name + "] [" + filename + "]");

	std::cout << "texture: loaded [" << name << "] at [" << filename << "]" << std::endl;

	Texture* texture = new Texture();
	texture->load(std::move(filename));
	m_textureManager.emplace(name, texture);
	return texture;
}

Texture* RessourceManager::get_texture(const std::string&& name)
{
	auto it = m_textureManager.find(name);

	if (it == m_textureManager.end())
		throw std::runtime_error("error: texture doesn't exist [" + name + "]");

	return it->second;
}

void RessourceManager::remove_texture(const std::string&& name)
{
	auto it = m_textureManager.find(name);

	if (it == m_textureManager.end())
		throw std::runtime_error("error: texture doesn't exist [" + name + "]");

	delete_texture(name, it->second);
	m_textureManager.erase(it);
}

void RessourceManager::delete_texture(const std::string name, Texture* texture)
{
	std::cout << "texture: deleted [" << name << "]" << std::endl;
	delete texture;
}
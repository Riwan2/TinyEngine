#ifndef RESSOURCE_MANAGER_H
#define RESSOURCE_MANAGER_H

#include <unordered_map>

#include "mesh.h"
#include "shader.h"
#include "texture.h"

class RessourceManager
{
public:
	RessourceManager();
	~RessourceManager();

	Mesh* load_mesh(const std::string&& name, const std::string&& filename);
	Shader* load_shader(const std::string&& name, const std::string&& vertexFile, const std::string&& fragmentFile);
	Texture* load_texture(const std::string&& name, const std::string&& filename);

	Mesh* get_mesh(const std::string&& name);
	Shader* get_shader(const std::string&& name);
	Texture* get_texture(const std::string&& name);

	void remove_mesh(const std::string&& name);
	void remove_shader(const std::string&& name);
	void remove_texture(const std::string&& name);

private:
	std::unordered_map<std::string, Mesh*> m_meshManager;
	std::unordered_map<std::string, Shader*> m_shaderManager;
	std::unordered_map<std::string, Texture*> m_textureManager;

	void delete_mesh(std::string name, Mesh* mesh);
	void delete_shader(std::string name, Shader* shader);
	void delete_texture(std::string name, Texture* texture);
};

#endif //RESSOURCE_MANAGER_H
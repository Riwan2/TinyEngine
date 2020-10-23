#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
}

void Mesh::render()
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_numTriangleIndices * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

/*
	init
*/

void Mesh::load(const std::string&& filename, bool info)
{
	load_from_file(("../ressource/mesh/" + filename).c_str(), info);
	setup_mesh(m_vertices, m_numVertices, m_indices, m_numTriangleIndices);

	delete[] m_vertices;
	delete[] m_indices;
}

void Mesh::init(Vertex* vertices, int numVertices, TriangleIndex* indices, int numIndices)
{
	setup_mesh(vertices, numVertices, indices, numIndices);
}

/*
	setup opengl mesh
*/

void Mesh::setup_mesh(Vertex* vertices, int numVertices, TriangleIndex* triangleIndices, int numTriangleIndices)
{
	m_numVertices = numVertices;
	m_numTriangleIndices = numTriangleIndices;

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numTriangleIndices * sizeof(TriangleIndex), triangleIndices, GL_STATIC_DRAW);

	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex::position)));

	//texture coordinate
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex::position) + sizeof(Vertex::normal)));

	glBindVertexArray(0);

	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}

/*
	load from obj file
*/

struct FaceIndex {
	int pos_index;
	int tex_index;
	int norm_index;
};

void Mesh::load_from_file(const char* filename, bool info)
{
	std::string debug_filename = std::string("[") + filename + std::string("]");

	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error(std::string("error: can't open obj file ") + debug_filename);
	}

	std::string line;
	bool vertices_created = false;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> list_indices;

	while (std::getline(file, line)) {
		if (line.size() > 64) {
			throw std::runtime_error(std::string("error: invalid line format ") + debug_filename);
		}

		if (line.front() == '#')
		{
			if (info) std::cout << "commented area: " << line.substr(2) << std::endl;
		}
		else if (line.front() == 'o')
		{
			if (info) std::cout << "obj name: " << line.substr(2) << std::endl;
		}
		else if (line.front() == 's')
		{
			if (info) std::cout << "smooth mode: " << line.substr(2) << std::endl;
		}
		else if (line.substr(0, 2) == "v ")
		{
			std::istringstream stream(line.substr(2));
			glm::vec3 pos;
			stream >> pos.x >> pos.y >> pos.z;
			if (stream.fail()) {
				throw std::runtime_error(std::string("error: invalid position ") + debug_filename);
			}
			positions.push_back(pos);
		}
		else if (line.substr(0, 2) == "vt")
		{
			std::istringstream stream(line.substr(3));
			glm::vec2 tex;
			stream >> tex.x >> tex.y;
			if (stream.fail()) {
				throw std::runtime_error(std::string("error: invalid texture coord ") + debug_filename);
			}
			texCoords.push_back(tex);
		}
		else if (line.substr(0, 2) == "vn")
		{
			std::istringstream stream(line.substr(3));
			glm::vec3 norm;
			stream >> norm.x >> norm.y >> norm.z;
			if (stream.fail()) {
				throw std::runtime_error(std::string("error: invalid normal ") + debug_filename);
			}
			normals.push_back(norm);
		}
		else if (line.substr(0, 2) == "f ")
		{
			if (!vertices_created) {
				m_vertices = new Vertex[positions.size()];
				m_numVertices = positions.size();
				vertices_created = true;
			}

			std::istringstream stream(line.substr(2));
			std::string indices_str;

			for (int i = 0; i < 3; i++) {
				std::getline(stream, indices_str, ' ');
				std::istringstream indices_stream(indices_str);
				std::string index_str;

				FaceIndex face_index;
				std::getline(indices_stream, index_str, '/');
				face_index.pos_index = std::stoi(index_str);

				std::getline(indices_stream, index_str, '/');
				face_index.tex_index = std::stoi(index_str);

				std::getline(indices_stream, index_str, '/');
				face_index.norm_index = std::stoi(index_str);

				list_indices.push_back(face_index.pos_index - 1);
				m_vertices[face_index.pos_index - 1].position = positions[face_index.pos_index - 1];
				m_vertices[face_index.pos_index - 1].normal = normals[face_index.norm_index - 1];
				m_vertices[face_index.pos_index - 1].texCoord = texCoords[face_index.tex_index - 1];
			}
		}
		else
		{
			throw std::runtime_error(std::string("error: invalid line format ") + debug_filename);
		}
	}
	
	//3 is the number of indices in a triangle
	m_numTriangleIndices = list_indices.size() / 3;
	m_indices = new TriangleIndex[m_numTriangleIndices];
	for (int i = 0; i < m_numTriangleIndices; i++) {
		int index = i * 3;
		m_indices[i].index1 = list_indices[index];
		m_indices[i].index2 = list_indices[++index];
		m_indices[i].index3 = list_indices[++index];
	}
}
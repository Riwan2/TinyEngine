#ifndef MAP_H
#define MAP_H

#include "../ressource/mesh.h"

//3D map
class Map {
public:
    Map(glm::vec2 size, glm::vec2 res, glm::vec3 position = glm::vec3(0.0));
    ~Map();

    //Init map with parameter
    //void init();

    //Render the map mesh
    void render() {
        m_mesh->render();
    }

    //getters and setters
    glm::vec3& position() { return m_position; }

private:
    glm::vec2 m_size;
    glm::vec2 m_resolution;
    glm::vec2 m_verticesDistance;
    glm::vec3 m_position;

    int m_numVertices, m_numTriangleIndices;
    Vertex* m_vertices;
    TriangleIndex* m_triangleIndices;

    Mesh* m_mesh;

    //Load the vao mesh
    void loadMesh();
};

#endif //MAP_H
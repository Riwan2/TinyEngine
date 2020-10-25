#ifndef MAP_H
#define MAP_H

#include "../ressource/mesh.h"

//2D height map
struct HeightMap {
    float* heigths;
    glm::vec2 size;

    void load(float* map, int sizeX, int sizeY) { 
        heigths = map;
        size = glm::vec2(sizeX, sizeY);
    }

    float getHeigth(int x, int y) {
        int index = y * size.x + x;
        return heigths[index];
    }

    ~HeightMap() { delete[] heigths; }
};

//3D map
class Map {
public:
    Map(glm::vec2 size, glm::vec2 res, glm::vec3 position = glm::vec3(0.0));
    ~Map();

    void render();
    float getMapHeigth(const glm::vec2& world_pos);
    glm::vec3 getMapNormal(const glm::vec2& world_pos);
    float getHeigth(float x, float y);
    glm::vec3 getNormal(int x, int y);

    //getters and setters
    glm::vec3& position() { return m_position; }

private:
    glm::vec2 m_size;
    glm::vec2 m_resolution;
    glm::vec2 m_verticesDistance;
    glm::vec3 m_position;

    int m_numVertices, m_numTriangleIndices, m_triangleIndex;
    Vertex* m_vertices;
    TriangleIndex* m_triangleIndices;

    HeightMap* m_heightMap;
    Mesh* m_mesh;

    //Load the vao mesh
    void loadMesh();
    void loadVertex(int vertexIndex, int x, int y);
    void loadTriangleIndices(int vertexIndex);
    glm::vec3 calculateNormal(float x, float y, float height);
    
};

#endif //MAP_H
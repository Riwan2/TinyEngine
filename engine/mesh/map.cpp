#include "map.h"

Map::Map(glm::vec2 size, glm::vec2 res, glm::vec3 position) {
    m_size = size;
    m_resolution = res;
    m_position = position;

    loadMesh();

    m_mesh = new Mesh();
    m_mesh->init(m_vertices, m_numVertices, m_triangleIndices, m_numTriangleIndices);

    delete[] m_vertices;
    delete[] m_triangleIndices;
}

Map::~Map() {
    delete m_mesh;
}

void Map::loadMesh() {
    m_numVertices = m_resolution.x * m_resolution.y;
    m_numTriangleIndices = (m_resolution.x - 1) * (m_resolution.y - 1) * 2;     //There is 2 triangle per quacd
    m_vertices = new Vertex[m_numVertices];
    m_triangleIndices = new TriangleIndex[m_numTriangleIndices];

    m_verticesDistance = m_size / m_resolution;

    for (int y = 0; y < m_resolution.y; y++) {
        for (int x = 0; x < m_resolution.x; x++) {
            int index = y * m_resolution.x + x;
            //position
            m_vertices[index].position.x = m_position.x - m_verticesDistance.x * x;
            m_vertices[index].position.y = m_position.y - m_verticesDistance.y * y;
            m_vertices[index].position.z = m_position.z;
            //normals
            m_vertices[index].normal.x = 0;
            m_vertices[index].normal.y = 0;
            m_vertices[index].normal.z = 0;
            //texCoord
            m_vertices[index].texCoord.x = 0;
            m_vertices[index].texCoord.y = 0;
        }
    }

    int index = 0;
    for (int y = 0; y < m_resolution.y - 1; y++) {
        for (int x = 0; x < m_resolution.x - 1; x++) {
            int vertexIndex = y * m_resolution.x + x;
            //vertex placement
            int topLeft = vertexIndex;
            int topRight = topLeft + 1;
            int botLeft = vertexIndex + m_resolution.x;
            int botRight = botLeft + 1;
            //indices
            m_triangleIndices[index].index1 = topRight;    //triangle 1
            m_triangleIndices[index].index2 = topLeft;
            m_triangleIndices[index].index3 = botLeft;
            index++;
            m_triangleIndices[index].index1 = botLeft;    //triangle 2
            m_triangleIndices[index].index2 = botRight;
            m_triangleIndices[index].index3 = topRight;
            index++;
        }
    }
}
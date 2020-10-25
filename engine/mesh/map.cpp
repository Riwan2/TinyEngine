#include "map.h"

Map::Map(glm::vec2 size, glm::vec2 res, glm::vec3 position) {
    m_size = size;
    m_resolution = res;
    m_position = position;

    m_numVertices = m_resolution.x * m_resolution.y;

    m_heightMap = new HeightMap();
    float* heights = new float[m_numVertices];

    for (int i = 0; i < m_numVertices; i++) {
        heights[i] = float(gmath::get_int(30)) / 30;
    }
    
    m_heightMap->load(heights, m_resolution.x, m_resolution.y);

    loadMesh();

    m_mesh = new Mesh();
    m_mesh->init(m_vertices, m_numVertices, m_triangleIndices, m_numTriangleIndices);

    delete[] m_triangleIndices;
}

Map::~Map() {
    delete[] m_vertices;
    delete m_heightMap;
    delete m_mesh;
}

//render : render the map mesh and disable face culling
void Map::render()
{
    //glDisable(GL_CULL_FACE);
    m_mesh->render();
    //glEnable(GL_CULL_FACE);
}

//getMapNormal : return the map normal for a 2D world position
glm::vec3 Map::getMapNormal(const glm::vec2& world_pos)
{
    glm::vec2 terrain = world_pos - glm::vec2(m_position.x, m_position.y);
    if (terrain.x < 0 || terrain.y < 0 || terrain.x > m_size.x || terrain.y > m_size.y)
        return glm::vec3(0, 1, 0);

    glm::vec2 grid;
    grid.x = floor(terrain.x / m_verticesDistance.x);
    grid.y = floor(terrain.y / m_verticesDistance.y);

    glm::vec2 quadCoord;
    quadCoord.x = fmodf(terrain.x, m_verticesDistance.x) / m_verticesDistance.x;
    quadCoord.y = fmodf(terrain.y, m_verticesDistance.y) / m_verticesDistance.y;

    glm::vec3 topLeft = getNormal(grid.x, grid.y);
    glm::vec3 topRight = getNormal(grid.x + 1, grid.y);
    glm::vec3 botLeft = getNormal(grid.x, grid.y + 1);
    glm::vec3 botRight = getNormal(grid.x + 1, grid.y + 1);

    if (quadCoord.x < 1 - quadCoord.y) {    //top left triangle
        return gmath::barryCentric(topLeft, topRight, botLeft, quadCoord);
    } else {    //bottom right triangle
        return gmath::barryCentric(topRight, botLeft, botRight, quadCoord);
    }
}

glm::vec3 Map::getNormal(int x, int y)
{
    if (x > 0 && y > 0 && x < m_resolution.x && y < m_resolution.y) {
        int index = x * m_resolution.x + y;
        return m_vertices[index].normal;
    }
    return glm::vec3(0, 1, 0);
}

//getMapHeight : return the map height for a 2D world position
float Map::getMapHeigth(const glm::vec2& world_pos)
{
    glm::vec2 terrain = world_pos - glm::vec2(m_position.x, m_position.y);
    if (terrain.x < 0 || terrain.y < 0 || terrain.x > m_size.x || terrain.y > m_size.y)
        return 0;

    glm::vec2 grid;
    grid.x = floor(terrain.x / m_verticesDistance.x);
    grid.y = floor(terrain.y / m_verticesDistance.y);

    glm::vec2 quadCoord;
    quadCoord.x = fmodf(terrain.x, m_verticesDistance.x) / m_verticesDistance.x;
    quadCoord.y = fmodf(terrain.y, m_verticesDistance.y) / m_verticesDistance.y;

    if (quadCoord.x < 1 - quadCoord.y) {    //top left triangle
        return gmath::barryCentricHeigth(glm::vec3(0, getHeigth(grid.x, grid.y), 0),
            glm::vec3(1, getHeigth(grid.x + 1, grid.y), 0),
            glm::vec3(0, getHeigth(grid.x, grid.y + 1), 1),
            quadCoord);
    } else {    //bottom right triangle
        return gmath::barryCentricHeigth(glm::vec3(1, getHeigth(grid.x + 1, grid.y), 0),
            glm::vec3(0, getHeigth(grid.x, grid.y + 1), 1),
            glm::vec3(1, getHeigth(grid.x + 1, grid.y + 1), 1),
            quadCoord);
    }
}

//getHeight : return the heightmap heigth at x and y position
float Map::getHeigth(float x, float y)
{
    return m_heightMap->getHeigth(x, y);
}

void Map::loadMesh() {
    m_vertices = new Vertex[m_numVertices];

    m_numTriangleIndices = (m_resolution.x - 1) * (m_resolution.y - 1) * 2;     //There is 2 triangle per quacd
    m_triangleIndices = new TriangleIndex[m_numTriangleIndices];
    m_triangleIndex = 0;

    m_verticesDistance = m_size / (m_resolution - glm::vec2(1));

    for (int y = 0; y < m_resolution.y; y++) {
        for (int x = 0; x < m_resolution.x; x++) {
            int index = y * m_resolution.x + x;
            loadVertex(index, x, y);

            if (y < m_resolution.y - 1 && x < m_resolution.x - 1) {
                loadTriangleIndices(index);
            }
        }
    }
}

//LoadVertex : load vertex with position, normal and texture coordinate
void Map::loadVertex(int vertexIndex, int x, int y)
{
    //height
    float heigth = getHeigth(x, y);
    //position
    m_vertices[vertexIndex].position.x = m_position.x + m_verticesDistance.x * x;
    m_vertices[vertexIndex].position.z = m_position.y + m_verticesDistance.y * y;
    m_vertices[vertexIndex].position.y = getHeigth(x, y);
    //normals
    glm::vec3 normal = calculateNormal(x, y, heigth);
    m_vertices[vertexIndex].normal = normal;
    //texCoord
    m_vertices[vertexIndex].texCoord.x = (1 / m_resolution.x) * x;
    m_vertices[vertexIndex].texCoord.y = (1 / m_resolution.y) * y;
}

//loadTriangleindices : load indices to form a quad
void Map::loadTriangleIndices(int vertexIndex)
{
    //vertex placement
    int topLeft = vertexIndex;
    int topRight = topLeft + 1;
    int botLeft = vertexIndex + m_resolution.x;
    int botRight = botLeft + 1;
    //indices
    m_triangleIndices[m_triangleIndex].index1 = topRight;    //triangle 1
    m_triangleIndices[m_triangleIndex].index2 = topLeft;
    m_triangleIndices[m_triangleIndex].index3 = botLeft;
    m_triangleIndex++;
    m_triangleIndices[m_triangleIndex].index1 = botLeft;    //triangle 2
    m_triangleIndices[m_triangleIndex].index2 = botRight;
    m_triangleIndices[m_triangleIndex].index3 = topRight;
    m_triangleIndex++;
}

//calculateNormal : calculate normal for given vertex and height
glm::vec3 Map::calculateNormal(float x, float y, float height)
{
    float v1, v2, v3, v4;
    if (x > 0 && x < m_heightMap->size.x - 1 && y > 0 && y < m_heightMap->size.y - 1) {
        v1 = getHeigth(x - 1, y);
        v2 = getHeigth(x + 1, y);
        v3 = getHeigth(x, y - 1);
        v4 = getHeigth(x, y + 1);
        return glm::normalize(glm::vec3(v1 - v2, 2.0, v3 - v4));
    } 
    return glm::vec3(0.0f, 1.0f, 0.0f);
}


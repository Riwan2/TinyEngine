#ifndef GMATH_H
#define GMATH_H

#include <glm/glm.hpp>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

/*
    cout operator to display math structure
*/

inline std::ostream& operator<<(std::ostream& os, const glm::vec2& vec)
{
    os << vec.x << " ; " << vec.y;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const glm::vec3& vec)
{
    os << vec.x << " ; " << vec.y << " ; " << vec.z;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const glm::quat& quat)
{
    os << quat.x << " ; " << quat.y << " ; " << quat.z << " ; " << quat.w;
    return os;
}

//math for game
namespace gmath {

inline void init_random()
{
    srand(time(NULL));
}

inline int get_int(int max)
{
    return rand() % max;
}

//lerp : return the result for 3d vector lerping, t is beetwin 0 and 1
inline glm::vec3 lerp(glm::vec3 v1, glm::vec3 v2, float t)
{
    auto d = (v2 - v1) * t;
    return v1 + d;
}

//lerp : return the result for float lerping, t is beetwin 0 and 1
inline float lerp(float v1, float v2, float t)
{
    t = 1 - powf(1 - t, 4.0);
    return v1 + (v2 - v1) * t;
}

//barryCentricHeigth : interpolate between 3D vertices from a 2D position vector, return only the y component
inline float barryCentricHeigth(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

//barryCentric : interpolate between 3D vertices from a 2D position vector, return the 3D results
inline glm::vec3 barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1 + l2 * p2 + l3 * p3;
}

};

#endif //GMATH_H
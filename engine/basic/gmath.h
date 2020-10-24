#ifndef GMATH_H
#define GMATH_H

#include <glm/glm.hpp>
#include <iostream>

//math for game
namespace gmath {

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

};

#endif //GMATH_H
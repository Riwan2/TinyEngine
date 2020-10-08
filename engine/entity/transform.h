#ifndef TRANSFORM_H
#define TRANSFORM_H

/* 
	Tiny Engine basic structure
*/

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct Transform
{
	Transform(glm::vec3 pos = glm::vec3(0.0), glm::vec3 rot = glm::vec3(0.0), glm::vec3 scl = glm::vec3(1.0)) 
	{
		position = pos;
		rotation = rot;
		scale = scl;
		quaternion = glm::quat(rotation);
		model = glm::mat4(1.0);
	}

	void update()
	{
		model = glm::mat4(1.0);
		model = glm::translate(model, position);

		model = glm::scale(model, scale);

		quaternion = glm::quat(rotation);
		model *= glm::toMat4(quaternion);
	}

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::quat quaternion;
	glm::mat4 model;
};

#endif //TRANSFORM_H
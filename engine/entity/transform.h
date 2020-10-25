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
		m_rotation = rot;
		scale = scl;
		quaternion = glm::quat(m_rotation);
		model = glm::mat4(1.0);
	}

	void update()
	{
		model = glm::mat4(1.0);
		model = glm::translate(model, position);

		model = glm::scale(model, scale);
		model *= glm::toMat4(quaternion);
	}

	void rotate(const glm::vec3& rot) 
	{
		m_rotation.x += glm::radians(fmod(rot.x, 360));
        m_rotation.y += glm::radians(fmod(rot.y, 360));
        m_rotation.z += glm::radians(fmod(rot.z, 360));
		quaternion = glm::quat(m_rotation);
	}

	void set_rotation(const glm::vec3& rot)
	{
		m_rotation.x = glm::radians(fmod(rot.x, 360));
        m_rotation.y = glm::radians(fmod(rot.y, 360));
        m_rotation.z = glm::radians(fmod(rot.z, 360));
		quaternion = glm::quat(m_rotation);
	}

	glm::vec3& rotation() { return m_rotation; }

	glm::vec3 position;
	glm::vec3 scale;

	glm::quat quaternion;
	glm::mat4 model;

private:
	glm::vec3 m_rotation;
};

#endif //TRANSFORM_H
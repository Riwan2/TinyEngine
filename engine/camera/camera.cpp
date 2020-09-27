#include "camera.h"

const float FOV = 45;
const float NEAR = 0.1f;
const float FAR = 100.0f;

Camera::Camera()
{
	position = glm::vec3(0.0, 0.0, 8.0);
	target = glm::vec3(0.0, 0.0, 0.0);

	m_viewMatrix = glm::mat4(1.0);
	m_orientation = glm::quat(0.0, 0.0, 0.0, 1.0);
}

Camera::~Camera()
{

}

void Camera::init(glm::vec2 displaySize)
{
	resize(displaySize);
}

void Camera::resize(glm::vec2 displaySize)
{
	m_displaySize = displaySize;
	m_projectionMatrix = glm::perspective(glm::radians(FOV), m_displaySize.x / m_displaySize.y, NEAR, FAR);
}

void Camera::update()
{
	m_orientation = glm::quatLookAt(glm::normalize(target - position), UP);
	
	Camera::basic_update();
}

void Camera::basic_update()
{
	glm::quat reverseOrient = glm::conjugate(m_orientation);

	glm::mat4 rotation = glm::toMat4(reverseOrient);
	glm::mat4 translation = glm::translate(glm::mat4(1.0), -position);

	m_viewMatrix = rotation * translation;
}

void Camera::move(glm::vec3 move)
{
	position += move;
}

void Camera::move_target(glm::vec3 move)
{
	target += move;
}
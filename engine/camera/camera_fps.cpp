#include "camera_fps.h"

CameraFPS::CameraFPS()
{
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
}

CameraFPS::~CameraFPS()
{

}

void CameraFPS::update()
{
	glm::quat quatX = glm::angleAxis(-glm::radians(m_yaw), UP);
	glm::quat quatY = glm::angleAxis(glm::radians(m_pitch), RIGHT);
	glm::quat quatZ = glm::angleAxis(glm::radians(m_roll), FRONT);

	m_orientation = quatX * quatY * quatZ;

	Camera::basic_update();
}

void CameraFPS::move_rotated(glm::vec3 move)
{
	position += m_orientation * move;
}

/*
	pitch yaw and roll
*/

void CameraFPS::set_pitch(float pitch)
{
	m_pitch = fmod(pitch, 360.0f);
}

void CameraFPS::set_yaw(float yaw)
{
	m_yaw = fmod(yaw, 360.0f);
}

void CameraFPS::set_roll(float roll)
{
	m_roll = fmod(roll, 360.0f);
}

void CameraFPS::move_pitch(float pitch)
{
	m_pitch = fmod(m_pitch + pitch, 360.0f);
}

void CameraFPS::move_yaw(float yaw)
{
	m_yaw = fmod(m_yaw + yaw, 360.0f);
}

void CameraFPS::move_roll(float roll)
{
	m_roll = fmod(m_roll + roll, 360.0f);
}
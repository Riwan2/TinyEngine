#include "camera_tps.h"

CameraTPS::CameraTPS()
{
	m_angleAround = 90.0f;
	m_angleY = -20.0f;
	m_roll = 0.0f;

	distance = 30.0;
}

CameraTPS::~CameraTPS()
{
	
}

void CameraTPS::update()
{
	float horizontalDistance = distance * cos(glm::radians(m_angleY));
	float verticalDistance = distance * sin(glm::radians(-m_angleY));

	position.x = horizontalDistance * cos(glm::radians(m_angleAround)) + target.x;
	position.y = verticalDistance + target.y;
	position.z = horizontalDistance * sin(glm::radians(m_angleAround)) + target.z;

	glm::quat quatX = glm::angleAxis(glm::radians(-m_angleAround + 90.0f), UP);
	glm::quat quatY = glm::angleAxis(glm::radians(m_angleY), RIGHT);
	glm::quat quatZ = glm::angleAxis(glm::radians(m_roll), FRONT);

	m_orientation = quatX * quatY * quatZ;

	Camera::basic_update();
}

/*
	angleAround, roll and angleX
*/

void CameraTPS::set_angleAround(float angle) 
{
	m_angleAround = fmod(angle, 360.0f);
}

void CameraTPS::set_angleY(float angle)
{
	m_angleY = fmod(-angle, 360.0f);
}

void CameraTPS::set_roll(float roll)
{
	m_roll = fmod(roll, 360.0f);
}

void CameraTPS::move_angleAround(float angle)
{
	m_angleAround = fmod(m_angleAround - angle, 360.0f);
}

void CameraTPS::move_angleY(float angle)
{
	m_angleY = fmod(m_angleY - angle, 360.0f);
}

void CameraTPS::move_roll(float roll)
{
	m_roll = fmod(m_roll + roll, 360.0f);
}

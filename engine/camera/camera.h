#ifndef CAMERA_H
#define CAMERA_H

#include "../basic/base.h"

const glm::vec3 RIGHT = glm::vec3(1.0, 0.0, 0.0);
const glm::vec3 UP = glm::vec3(0.0, 1.0, 0.0);
const glm::vec3 FRONT = glm::vec3(0.0, 0.0, 1.0);

class Camera
{
public:
	Camera();
	~Camera();

	void init(glm::vec2 displaySize);
	void resize(glm::vec2 displaySize);
	
	virtual void update();

	void move(glm::vec3 move);
	void move_target(glm::vec3 move);

	glm::mat4 projection_view() { return m_projectionMatrix * m_viewMatrix; }

	glm::vec3 position;
	glm::vec3 target;

protected:		
	glm::quat m_orientation;

	void basic_update();

private:
	glm::vec2 m_displaySize;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
};

#endif //CAMERA_H
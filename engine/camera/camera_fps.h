#ifndef CAMERA_FPS_H
#define CAMERA_FPS_H

#include "camera.h"

class CameraFPS : public Camera
{
public:
	CameraFPS();
	~CameraFPS();

	virtual void update() override;

	//move by taking rotation into account
	void move_rotated(glm::vec3 move);

	//pitch yaw and roll angle in degree
	void set_pitch(float pitch);
	void set_yaw(float yaw);
	void set_roll(float roll);

	void move_pitch(float pitch);
	void move_yaw(float yaw);
	void move_roll(float roll);

	float pitch() { return m_pitch; }
	float yaw() { return m_yaw; }
	float roll() { return m_roll; }

private:
	float m_pitch;
	float m_yaw;
	float m_roll;
};

#endif //CAMERA_FPS_H
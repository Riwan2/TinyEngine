#ifndef CAMERA_TPS_H
#define CAMERA_TPS_H

#include "camera.h"

class CameraTPS : public Camera
{
public:
	CameraTPS();
	~CameraTPS();

	virtual void update() override;

	//roll, angleY and angleAround set in degree
	void set_angleAround(float angle);
	void set_angleY(float angle);
	void set_roll(float roll);

	void move_angleAround(float angle);
	void move_angleY(float angle);
	void move_roll(float roll);

	float angleAround() { return m_angleAround; }
	float angleY() { return m_angleY; }
	float roll() { return m_roll; }

	float distance;

private:
	float m_angleAround;
	float m_angleY;
	float m_roll;
};

#endif //CAMERA_TPS_H
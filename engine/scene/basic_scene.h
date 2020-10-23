#ifndef BASIC_SCENE_H
#define BASIC_SCENE_H

#include "scene.h"
#include "../camera/camera_tps.h"

#include "../mesh/map.h"

class BasicScene : public Scene
{
public:
	BasicScene();
	~BasicScene();

	virtual void load() override;
	virtual void update() override;
	virtual void game_gui() override;

	virtual void resize() override;

	CameraTPS* camera() { return m_camera; };

private:
	CameraTPS* m_camera;
	Map* m_map;
};

#endif //BASIC_SCENE_H
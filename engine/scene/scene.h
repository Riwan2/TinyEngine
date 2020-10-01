#ifndef SCENE_H
#define SCENE_H

#include "../ressource/ressource_manager.h"
#include "../gui/renderer_2d.h"
#include "../basic/app_util.h"



class Scene
{
public:
	Scene() {
		m_ressourceManager = new RessourceManager();
	}

	virtual ~Scene() {
		delete m_ressourceManager;
	}
	
	virtual void load() = 0;
	virtual void update() = 0;
	virtual void game_gui() = 0;

	virtual void resize() = 0;

protected:
	RessourceManager* ressourceManager() { return m_ressourceManager; }

private:
	RessourceManager* m_ressourceManager;
};

#endif //SCENE_H
#ifndef SCENE_H
#define SCENE_H

#include "../ressource/ressource_manager.h"
#include "../basic/app_util.h"

class App;

class Scene
{
public:
	Scene();
	~Scene();

	virtual void init();
	virtual void load() = 0;
	virtual void update() = 0;

	virtual void resize() = 0;

protected:
	RessourceManager* ressourceManager() { return m_ressourceManager; }

private:
	RessourceManager* m_ressourceManager;
};

#endif //SCENE_H
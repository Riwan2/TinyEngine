#ifndef SCENE_H
#define SCENE_H

#include "../ressource/ressource_manager.h"
#include "../gui/renderer_2d.h"
#include "../basic/app_util.h"



class Scene
{
public:
	virtual ~Scene() {}

	void init(Renderer2D* renderer2D)
	{
		m_ressourceManager = new RessourceManager();
		m_renderer2D = renderer2D;
	}

	void cleanup() {
		delete m_ressourceManager;
	}
	
	virtual void load() = 0;
	virtual void update() = 0;
	virtual void game_gui() = 0;

	virtual void resize() = 0;

protected:
	RessourceManager* ressourceManager() { return m_ressourceManager; }
	Renderer2D* renderer2D() { return m_renderer2D; }

private:
	RessourceManager* m_ressourceManager;
	Renderer2D* m_renderer2D;
};

#endif //SCENE_H
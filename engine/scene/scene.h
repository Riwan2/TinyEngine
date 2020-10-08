#ifndef SCENE_H
#define SCENE_H

#include "../ressource/ressource_manager.h"
#include "../gui/renderer_2d.h"
#include "../basic/app_util.h"

#include "../component/component.h"
#include "../render/renderer.h"

class Scene
{
public:
	Scene() {
		m_ressourceManager = new RessourceManager();
		m_entityManager = new EntityManager();
		m_renderer = new Renderer();
	}

	virtual ~Scene() {
		delete m_renderer;
		delete m_entityManager;
		delete m_ressourceManager;
	}
	
	virtual void load() = 0;
	virtual void update() = 0;
	virtual void game_gui() = 0;

	void render()
	{
		auto batch = entityManager()->entities_batch().begin();
        while (batch != entityManager()->entities_batch().end()) {
			renderer()->render_batch(batch->second);
            batch++;
        }

        auto entity = entityManager()->entities().begin();
        while (entity != entityManager()->entities().end()) {
			renderer()->render(entity->second);
            entity++;
        }
	}

	virtual void resize() = 0;

protected:
	RessourceManager* ressourceManager() { return m_ressourceManager; }
	EntityManager* entityManager() { return m_entityManager; }
	Renderer* renderer() { return m_renderer; }

private:
	RessourceManager* m_ressourceManager;
	EntityManager* m_entityManager;
	Renderer* m_renderer;
};

#endif //SCENE_H
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "basic_scene.h"
#include "menu_scene.h"

class SceneManager : public ScenePicker
{
public:
    SceneManager() {
        m_scene = nullptr;
    }

    ~SceneManager() {}

    virtual void load_scene(eScene sceneType) override
    {
        delete_scene();

        switch(sceneType) {
            case menu:
                m_scene = new MenuScene();
                break;
            case basic:
                m_scene = new BasicScene();
                break;
            default:
                break;
        }

        std::cout << "•scene loading" << std::endl;

        m_scene->bind_sceneManager(this);
        m_scene->load();
    }

    void update()
    {
        if (m_scene != nullptr) {
            m_scene->update();
        }
    }

    void cleanup()
    {
        delete_scene();
    }

    void game_gui()
    {
        if (m_scene != nullptr)
            m_scene->game_gui();
    }

    void resize()
    {
        if (m_scene != nullptr)
            m_scene->resize();
    }

    Scene* scene() { return m_scene; }

private:
    Scene* m_scene;

    void delete_scene()
    {
        if (m_scene != nullptr) {
            std::cout << "•scene delete" << std::endl;
            delete m_scene;
        }
    }
};

#endif //SCENE_MANAGER_H
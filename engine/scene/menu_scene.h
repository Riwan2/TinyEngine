#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "scene.h"

class MenuScene : public Scene 
{
public:
    MenuScene();
    ~MenuScene();

    virtual void load() override;
    virtual void update() override;
    virtual void game_gui() override;

    virtual void resize() override;
};

#endif //MENU_SCENE_H
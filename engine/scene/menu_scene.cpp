#include "menu_scene.h"

MenuScene::MenuScene()
{

}

MenuScene::~MenuScene()
{

}

void MenuScene::load()
{

}

void MenuScene::update() 
{
    if (Input::keyPressed(SDLK_RETURN)) {
        sceneManager()->load_scene(eScene::basic);
    }
}

void MenuScene::game_gui() 
{
    Renderer2D::begin();
    
    glm::vec2 screen = AppUtil::displaySize();

    Renderer2D::renderQuad(glm::vec2(50, 50), glm::vec2(screen.x - 100, screen.y - 100), glm::vec3(0.5, 0.2, 0.2));
    Renderer2D::renderQuad(glm::vec2(100, 100), glm::vec2(screen.x - 200, screen.y - 200), glm::vec3(0.8, 0.5, 0.5));

    Renderer2D::end();
}

void MenuScene::resize()
{

}
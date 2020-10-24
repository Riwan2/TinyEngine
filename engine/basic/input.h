#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <map>

class Input
{
public:
    static void init();
    
    static void update();
    static void processEvent(SDL_Event* event);

    //keyDown : return true if the key is pressed down
    static bool keyDown(SDL_KeyCode key);
    //keyPressed : return true if the key is just pressed
    static bool keyPressed(SDL_KeyCode key);

    //mouseScroll : return the mouse scrolling from the last frame
    static glm::vec2 mouseScroll();

private:
    static Uint8 m_keystates[SDL_NUM_SCANCODES];
    static Uint8 m_last_keystates[SDL_NUM_SCANCODES];

    static glm::vec2 m_mouseScroll;
    static glm::vec2 m_lastMouseScroll;
};

#endif //INPUT_H
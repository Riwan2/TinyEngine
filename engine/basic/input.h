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

    static bool keyDown(SDL_KeyCode key);
    static bool keyPressed(SDL_KeyCode key);

private:
    static Uint8 m_keystates[SDL_NUM_SCANCODES];
    static Uint8 m_last_keystates[SDL_NUM_SCANCODES];
};

#endif //INPUT_H
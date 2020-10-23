#include "input.h"

Uint8 Input::m_keystates[SDL_NUM_SCANCODES];
Uint8 Input::m_last_keystates[SDL_NUM_SCANCODES];

void Input::init()
{
    memset(m_last_keystates, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
    memcpy(m_keystates, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

void Input::update()
{
    memcpy(m_last_keystates, m_keystates, sizeof(Uint8) * SDL_NUM_SCANCODES);
    memcpy(m_keystates, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

bool Input::keyDown(SDL_KeyCode key)
{
    SDL_Scancode code = SDL_GetScancodeFromKey(key);
    return m_keystates[code] && m_last_keystates[code];
}

bool Input::keyPressed(SDL_KeyCode key)
{
    SDL_Scancode code = SDL_GetScancodeFromKey(key);
    return m_keystates[code] && !m_last_keystates[code];
}
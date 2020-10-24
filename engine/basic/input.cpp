#include "input.h"

Uint8 Input::m_keystates[SDL_NUM_SCANCODES];
Uint8 Input::m_last_keystates[SDL_NUM_SCANCODES];

glm::vec2 Input::m_mouseScroll;
glm::vec2 Input::m_lastMouseScroll;

void Input::init()
{
    memset(m_last_keystates, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
    memcpy(m_keystates, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);

    m_mouseScroll = glm::vec2(0, 0);
    m_lastMouseScroll = glm::vec2(0, 0);
}

void Input::update()
{
    memcpy(m_last_keystates, m_keystates, sizeof(Uint8) * SDL_NUM_SCANCODES);
    memcpy(m_keystates, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);

    m_mouseScroll = glm::vec2(0, 0);
    m_lastMouseScroll = glm::vec2(0, 0);
}

void Input::processEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_MOUSEWHEEL:
            m_lastMouseScroll = m_mouseScroll;
            m_mouseScroll = glm::vec2(event->wheel.x, event->wheel.y);
            break;
        default:
            break;
    }
}

//Mouse event
glm::vec2 Input::mouseScroll()
{
    return m_mouseScroll - m_lastMouseScroll;
}

//Key event
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
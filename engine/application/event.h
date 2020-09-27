#ifndef EVENT_H
#define EVENT_H

#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl.h"
#include "../imgui/imgui_impl_opengl3.h"

class Event
{
public:
	Event();
	~Event();

	void update();

	virtual void on_quit() {}
	virtual void on_resize() {}

	glm::vec2 displaySize() { return m_displaySize; }

protected:
	void init(glm::vec2 displaySize);

private:
	glm::vec2 m_displaySize;

};

#endif //EVENT_H
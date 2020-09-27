#include "event.h"

Event::Event()
{
	m_displaySize = glm::vec2(0.0, 0.0);
}

Event::~Event()
{
	
}

void Event::init(glm::vec2 displaySize)
{
	m_displaySize = displaySize;
}

void Event::update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);

		if (event.type == SDL_QUIT) 
		{
			on_quit();
		}
		else if (event.type == SDL_KEYDOWN) 
		{
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					on_quit();
					break;
				default:
					break;
			}
		}
		else if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				m_displaySize.x = event.window.data1;
				m_displaySize.y = event.window.data2;
				on_resize();
			}
		}
	}
}
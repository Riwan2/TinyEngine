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
	Input::init();
}

void Event::update()
{
	SDL_Event event;

	if (Input::keyPressed(SDLK_ESCAPE))
		on_quit();

	Input::update();

	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);

		switch (event.type) {
			case SDL_QUIT:
				on_quit();
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					m_displaySize.x = event.window.data1;
					m_displaySize.y = event.window.data2;
					on_resize();
				}
				break;
		}
	}
}
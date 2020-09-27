#ifndef APP_H
#define APP_H

#include "event.h"

#include "../scene/basic_scene.h"
#include "../render/frame_buffer.h"
#include "../gui/renderer_2d.h"

#include <stdexcept>

class App : public Event
{
public:
	App();
	~App();

	void run() {
		init();
		load();
		while (running) {
			update();
		}
		cleanup();
	}

	void init();
	void load();
	void update();
	void cleanup();

	void debug_gui();
	void game_gui();

	virtual void on_quit() override;
	virtual void on_resize() override;

	bool running;

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	BasicScene* m_basicScene;
	FrameBuffer* m_framebuffer;
	Renderer2D* m_renderer2D;

	void init_sdl();
	void init_gl();
	void init_imgui();
};

#endif //APP_H
#ifndef APP_H
#define APP_H

#include "event.h"

#include "../scene/basic_scene.h"
#include "../render/frame_buffer.h"
#include "../gui/renderer_2d.h"

#include "../entity/ecs.h"

#include <stdexcept>

class App : public Event
{
public:
	App();
	~App();

	void run() {
		init();

		TimeProfiler::begin();
		load();
		TimeProfiler::end("loading time");

		while (running) {
			//TimeProfiler::begin();
			update();
			//TimeProfiler::end("update time");
		}

		TimeProfiler::begin();
		cleanup();
		TimeProfiler::end("clean up time");
	}

	void init();
	void load();
	void update();
	void cleanup();

	void screen_render();
	void debug_gui();
	void game_gui();

	virtual void on_quit() override;
	virtual void on_resize() override;

	bool running;

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	Scene* m_basicScene;
	FrameBuffer* m_framebuffer;

	Shader* m_screenShader;
	Texture* m_noiseTexture;

	void init_sdl();
	void init_gl();
	void init_imgui();
};

#endif //APP_H
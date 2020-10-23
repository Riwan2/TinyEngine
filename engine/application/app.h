#ifndef APP_H
#define APP_H

#include <stdexcept>

#include "event.h"
#include "../render/frame_buffer.h"
#include "../gui/renderer_2d.h"

#include "../entity/ecs.h"
#include "../scene/scene_manager.h"

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

	void screen_render();
	void debug_gui();
	void game_gui();

	virtual void on_quit() override;
	virtual void on_resize() override;

	bool running;

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	FrameBuffer* m_framebuffer;
	SceneManager* m_sceneManager;

	Shader* m_screenShader;
	Texture* m_noiseTexture;

	void init_sdl();
	void init_gl();
	void init_imgui();
};

#endif //APP_H
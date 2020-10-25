#include "app.h"

const char* TITLE = "TinyEngine";
const int DISPLAY_WIDTH = 1000;
const int DISPLAY_HEIGHT = 600;
const int POS_X = SDL_WINDOWPOS_CENTERED;
const int POS_Y = SDL_WINDOWPOS_CENTERED;
const glm::vec4 CLEAR_COLOR = glm::vec4(0.12, 0.12, 0.12, 1.0);

#define DEBUG 1

App::App()
{
	running = true;
}

App::~App()
{

}

/*
	init OpenGL and SDL2 stuff
*/

void App::init()
{
	init_sdl();
	init_gl();
	init_imgui();	

	gmath::init_random();

	Event::init(glm::vec2(DISPLAY_WIDTH, DISPLAY_HEIGHT));
	AppUtil::set_displaySize(displaySize());
	AppUtil::set_clearColor(CLEAR_COLOR);
}

/*
	load asset
*/

void App::load()
{
	m_framebuffer = new FrameBuffer();
	m_framebuffer->init(displaySize());

	Renderer2D::init(displaySize());

	m_sceneManager = new SceneManager();
	m_sceneManager->load_scene(eScene::basic);

	m_screenShader = new Shader();
	m_screenShader->load("screen.vr", "screen.fa");

	m_noiseTexture = new Texture();
	m_noiseTexture->load("noise.jpg");
}

/*
	update loop
*/

static bool polygonMode = true;

void App::update()
{
	Event::update();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
	
	if (DEBUG)
		debug_gui();

	//first render pass
	m_framebuffer->bind();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	if (Input::keyPressed(SDLK_p)) {
		polygonMode = !polygonMode;
	}

	if (polygonMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glViewport(0, 0, displaySize().x, displaySize().y);
	glClearColor(AppUtil::clearColor().r, AppUtil::clearColor().g, AppUtil::clearColor().b, AppUtil::clearColor().a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	m_sceneManager->update();

	//second render pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, displaySize().x, displaySize().y);

	screen_render();
	game_gui();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(m_window);
}

/*
	all the effect on screen
*/

void App::screen_render()
{
	m_screenShader->bind();

	static float time = 0;
	time += 0.01f;
	m_screenShader->set_float("time", time);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_framebuffer->textureID());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_noiseTexture->textureID());

	m_screenShader->set_int("aTexture", 0);
	m_screenShader->set_int("aNoise", 1);

	Renderer2D::render_screen();
}

/*
	gui imgui debug
*/

void App::debug_gui()
{
}

/*
	gui custom game
*/

void App::game_gui()
{
	m_sceneManager->game_gui();
}

/* 
	override virtual function
*/

void App::on_quit()
{
	running = false;
}

void App::on_resize()
{
	AppUtil::set_displaySize(displaySize());
	m_sceneManager->resize();

	Renderer2D::resize(displaySize());
	m_framebuffer->resize(displaySize());
}

/*
	clean up
*/

void App::cleanup()
{
	std::cout << "\nCLEAN UP" << std::endl;
	delete m_noiseTexture;
	delete m_screenShader;

	m_sceneManager->cleanup();
	Renderer2D::cleanup();

	delete m_framebuffer;
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

/*
	openGL stuff
*/

void App::init_gl()
{
	//glew
	GLenum res = glewInit();
	
	if (GLEW_OK != res) {
		throw std::runtime_error(std::string("glew init error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(res))));
	}

	//cull face
	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void App::init_sdl()
{
	//init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw std::runtime_error(std::string("SDL2 init error: ") + SDL_GetError());
	}

	//version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    //buffer
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //window
    int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	m_window = SDL_CreateWindow(TITLE, POS_X, POS_Y, DISPLAY_WIDTH, DISPLAY_HEIGHT, flags);

	if (m_window == NULL) {
		throw std::runtime_error(std::string("window creation error: ") + SDL_GetError());
	}

	//context
	m_glContext = SDL_GL_CreateContext(m_window);
}

/*
	imgui init
*/

void App::init_imgui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(m_window, m_glContext);
	const char* glsl_version = "#version 330";
	ImGui_ImplOpenGL3_Init(glsl_version);
}
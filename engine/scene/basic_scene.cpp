#include "basic_scene.h"

BasicScene::BasicScene()
{
	m_camera = new CameraTPS();
	m_camera->init(AppUtil::displaySize());

	renderer()->set_camera(m_camera);

	//m_camera->target = glm::vec3(0.0, 3.75, 0.0);
	m_camera->target = glm::vec3(0.0);
	m_camera->distance = 10;
	//m_camera->set_angleY(120);

	m_map = new Map(glm::vec2(5.0, 5.0), glm::vec2(10, 10), glm::vec3(2.5, 2.5, 0));
}

BasicScene::~BasicScene()
{
	delete m_camera;
	delete m_map;
}

void BasicScene::load()
{
	//Mesh* mesh = ressourceManager()->load_mesh("dragon", "dragon.obj");
	Texture* texture = ressourceManager()->load_texture("grass", "grass.jpg");
	Shader* shader = ressourceManager()->load_shader("shader", "map.vr", "map.fa");

	//Entity* entity = new Entity(mesh, texture, shader);
	//entityManager()->add_entity("dragon", entity);
}

bool scroll = false;
float begin = 0;
float amount = 0;
float timer = 0.0;

void BasicScene::update()
{
	//m_camera->move_angleAround(0.5);
	if (Input::keyDown(SDLK_RIGHT)) 
		m_camera->move_target(glm::vec3(0.1, 0, 0));
	else if (Input::keyDown(SDLK_LEFT))
		m_camera->move_target(glm::vec3(-0.1, 0, 0));

	if (Input::keyDown(SDLK_UP))
		m_camera->move_target(glm::vec3(0, 0, 0.1));
	else if (Input::keyDown(SDLK_DOWN))
		m_camera->move_target(glm::vec3(0, 0, -0.1));

	auto angle = m_camera->angleAround();

	if (Input::mouseScroll().x != 0) {
		if (!scroll && (Input::mouseScroll().x > 4 || Input::mouseScroll().x < -4)) {
			scroll = true;
			amount = Input::mouseScroll().x;
			begin = m_camera->angleAround();
		} else {
			angle = m_camera->angleAround() + Input::mouseScroll().x * 2;
		}
	}

	if (scroll) {
		timer += 0.01;
		angle = gmath::lerp(begin, begin + amount * 50, timer);
		if (timer >= 1) {
			timer = 0;
			scroll = false;
		}
	}

	m_camera->set_angleAround(angle);

	if (timer >= 0.3 || timer == 0)
		m_camera->move_angleY(Input::mouseScroll().y * 2);
	m_camera->update();

	//auto dragon = entityManager()->get_entity("dragon");
	//dragon->move(glm::vec3(0.01, 0.0, 0.0));

	//glDisable(GL_CULL_FACE);
	auto shader = ressourceManager()->get_shader("shader");

	static Transform t;
	t.rotation = glm::vec3(1.62, 0, 0);
	t.update();

	shader->bind();
	shader->set_mat4("model", t.model);
	shader->set_mat4("projection_view", m_camera->projection_view());

	m_map->render();

	entityManager()->update();
	Scene::render();
} 

void BasicScene::game_gui()
{
	// Renderer2D::begin();
	// Renderer2D::renderQuad(glm::vec2(100, 100), glm::vec2(50, 50), glm::vec3(0.5, 0.1, 0.2));
	// Renderer2D::end();
}

void BasicScene::resize()
{
	m_camera->resize(AppUtil::displaySize());
}

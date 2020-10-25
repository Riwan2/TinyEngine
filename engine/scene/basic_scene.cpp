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

	auto size = glm::vec2(10, 10);
	m_map = new Map(size, glm::vec2(10, 10), glm::vec3(-size.x / 2, -size.y / 2, 0.0));
}

BasicScene::~BasicScene()
{
	delete m_camera;
	delete m_map;
}

void BasicScene::load()
{
	//Mesh* mesh = ressourceManager()->load_mesh("dragon", "dragon.obj");
	Mesh* mesh = ressourceManager()->load_mesh("cube", "cube.obj");
	Texture* texture = ressourceManager()->load_texture("grass", "grass.jpg");
	ressourceManager()->load_shader("shader", "map/map.vr", "map/map.fa");
	Shader* shader = ressourceManager()->load_shader("cubeShader", "shader.vr", "shader.fa");

	//Entity* entity = new Entity(mesh, texture, shader);
	//entityManager()->add_entity("dragon", entity);

	auto player = entityManager()->add_entity("player", new Entity(mesh, texture, shader));
	player->scale(glm::vec3(0.1));
	player->move(glm::vec3(1.2, 0.0, 0.1));
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

	m_camera->move_angleAround(Input::mouseScroll().x * 3);
	m_camera->move_angleY(Input::mouseScroll().y * 2);
	m_camera->update();

	//auto dragon = entityManager()->get_entity("dragon");
	//dragon->move(glm::vec3(0.01, 0.0, 0.0));

	auto player = entityManager()->get_entity("player");

	if (Input::keyDown(SDLK_d))
		player->move(glm::vec3(0.05, 0, 0));
	else if (Input::keyDown(SDLK_q))
		player->move(glm::vec3(-0.05, 0, 0));

	if (Input::keyDown(SDLK_z))
		player->move(glm::vec3(0, 0.0, -0.05));
	else if (Input::keyDown(SDLK_s))
		player->move(glm::vec3(0, -0.0, 0.05));

	auto pos = player->transform()->position;
	auto h = m_map->getMapHeigth(glm::vec2(pos.x, pos.z));
	player->transform()->position.y = h;

	auto norm = m_map->getMapNormal(glm::vec2(pos.x, pos.z));

	if (glm::any(glm::isnan(norm)))
		norm = glm::vec3(0, 1, 0);

	//glDisable(GL_CULL_FACE);
	auto shader = ressourceManager()->get_shader("shader");

	shader->bind();
	shader->set_mat4("model", glm::mat4(1.0));
	shader->set_mat4("projection_view", m_camera->projection_view());

	ressourceManager()->get_texture("grass")->bind();
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

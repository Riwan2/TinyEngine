#include "basic_scene.h"

BasicScene::BasicScene()
{
	m_camera = new CameraTPS();
	m_camera->init(AppUtil::displaySize());

	renderer()->set_camera(m_camera);

	m_camera->target = glm::vec3(0.0, 3.75, 0.0);
	m_camera->distance = 20;
	m_camera->set_angleY(20);

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

void BasicScene::update()
{
	//m_camera->move_angleAround(0.5);
	m_camera->target = glm::vec3(0.0);
	m_camera->distance = 10;
	m_camera->Camera::update();

	glDisable(GL_CULL_FACE);

	//auto dragon = entityManager()->get_entity("dragon");
	//dragon->move(glm::vec3(0.01, 0.0, 0.0));

	//glDisable(GL_CULL_FACE);
	auto shader = ressourceManager()->get_shader("shader");

	shader->bind();
	shader->set_mat4("model", glm::mat4(1.0));
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

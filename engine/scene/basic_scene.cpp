#include "basic_scene.h"

BasicScene::BasicScene()
{
	m_camera = new CameraTPS();
	m_camera->init(AppUtil::displaySize());

	m_camera->target = glm::vec3(0.0, 3.75, 0.0);
	m_camera->distance = 20;
	m_camera->set_angleY(20);
}

BasicScene::~BasicScene()
{
	delete m_camera;
}

Texture* texture;

void BasicScene::load()
{
	ressourceManager()->load_mesh("dragon", "dragon.obj");	
	ressourceManager()->load_shader("shader", "shader.vr", "shader.fa");
	ressourceManager()->load_texture("grass", "grass.jpg");
}

void BasicScene::update()
{
	Transform transform;
	transform.update();

	m_camera->move_angleAround(0.5);
	m_camera->update();

	Shader* shader = ressourceManager()->get_shader("shader");
	shader->bind();

	shader->set_mat4("model", transform.model);
	shader->set_mat4("projection_view", m_camera->projection_view());
	shader->set_vec3("view_pos", m_camera->position);

	ressourceManager()->get_texture("grass")->bind();
	ressourceManager()->get_mesh("dragon")->render();
}

void BasicScene::game_gui()
{
}

void BasicScene::resize()
{
	m_camera->resize(AppUtil::displaySize());
}

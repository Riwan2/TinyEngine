#include "basic_scene.h"

BasicScene::BasicScene()
{
	m_camera = new CameraTPS();
	m_camera->init(AppUtil::displaySize());

	renderer()->set_camera(m_camera);

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
	Mesh* mesh = ressourceManager()->load_mesh("dragon", "dragon.obj");
	Texture* texture = ressourceManager()->load_texture("grass", "grass.jpg");
	Shader* shader = ressourceManager()->load_shader("shader", "shader.vr", "shader.fa");

	entityManager()->add_batch("tree");
	auto trees = entityManager()->get_batch("tree");

	for (int i = 0; i < 1; i++) {
		Entity* entity = new Entity(mesh, texture, shader);
		entity->transform()->scale = glm::vec3(0.1);
		entity->transform()->position = glm::vec3(i * 1.5 - 7.5, 3.0, 0.0);
		entity->transform()->update();

		trees->push_back(entity);
	}
}

void BasicScene::update()
{
	Transform transform;
	transform.update();

	m_camera->move_angleAround(0.5);
	m_camera->update();

	entityManager()->update();
}

void BasicScene::game_gui()
{
	
}

void BasicScene::resize()
{
	m_camera->resize(AppUtil::displaySize());
}

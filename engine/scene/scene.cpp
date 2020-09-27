#include "scene.h"

Scene::Scene()
{
	
}

Scene::~Scene()
{
	delete m_ressourceManager;
}

void Scene::init()
{
	m_ressourceManager = new RessourceManager();
}
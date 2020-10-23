#include "renderer.h"

Renderer::Renderer()
{
    m_camera = nullptr;
}

Renderer::~Renderer()
{

}

void Renderer::render(Entity* entity)
{
    update_transform(entity);

    auto shader = entity->shader();
    shader->bind();

    shader->set_mat4("model", entity->transform()->model);
    shader->set_mat4("projection_view", m_camera->projection_view());
    shader->set_vec3("view_pos", m_camera->position);

    entity->texture()->bind();
    entity->mesh()->render();
}

void Renderer::render_batch(std::vector<Entity*>* batch)
{
    for (auto entity : *batch) {
        update_transform(entity);

        Shader* shader = entity->shader();
	    shader->bind();

	    shader->set_mat4("model", entity->transform()->model);
	    shader->set_mat4("projection_view", m_camera->projection_view());
	    shader->set_vec3("view_pos", m_camera->position);

        entity->texture()->bind();
        entity->mesh()->render();
    }
}

void Renderer::set_camera(Camera* camera)
{
    m_camera = camera;
}

void Renderer::update_transform(Entity* entity)
{
    if (entity->moved) {
        entity->moved = false;
        entity->transform()->update();
    }
}
#ifndef ECS_H
#define ECS_H

#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>
#include <unordered_map>

#include "transform.h"
#include "../basic/time_profiler.h"

#include "../ressource/mesh.h"
#include "../ressource/shader.h"
#include "../ressource/texture.h"

class Entity;

/*
    component
*/

class Component
{
public:
    Component() {}
    virtual ~Component() {}

    void link(Entity* entity) { m_entity = entity; }
    virtual void update() = 0;

protected:
    Entity* entity() { return m_entity; }

private:
    Entity* m_entity;
};

class BasicComponent : public Component
{
public:
    void update() override {
        //std::cout << "basic update" << std::endl;
    }    
};

class PowerComponent : public Component
{
    void update() override {
        //std::cout << "power update" << std::endl;
    }
};

/*
    component manager
*/

class ComponentManager
{
public:
    ComponentManager(Entity* entity) { m_entity = entity; }

    ~ComponentManager()
    {
        for (auto component : m_components) {
            std::string name = typeid(*component).name();
            delete_component(component, std::move(name));
        }
    }

    void update()
    {
        for (auto component : m_components) {
            component->update();
        }
    }

    template <class T>
    void add(T *component)
    {
        std::string name = typeid(T).name();

        for (auto component : m_components) {
            if (dynamic_cast<T *>(component)) {
                throw std::runtime_error("error: component already exist [" + name + "]");
            }
        }

        //std::cout << "component: added [" + name + "]" << std::endl;
        component->link(m_entity);
        m_components.push_back(component);
    }

    template <class T>
    Component *get()
    {
        std::string name = typeid(T).name();
        Component *target = nullptr;

        for (auto component : m_components) {
            if (dynamic_cast<T *>(component)) {
                target = component;
            }
        }

        if (target != nullptr) {
            return target;
        } else {
            throw std::runtime_error("error: component doesn't exist [" + name + "]");
        }
    }

    template <class T>
    void remove()
    {
        std::string name = typeid(T).name();
        Component *target = get<T>();
        int index;

        for (int i = 0; i < m_components.size(); i++) {
            if (m_components[i] == target) {
                index = i;
                break;
            }
        }

        m_components.erase(m_components.begin() + index);
        delete_component(target, std::move(name));
    }

private:
    std::vector<Component *> m_components;
    Entity* m_entity;

    void delete_component(Component *comp, std::string &&name)
    {
        delete comp;
        //std::cout << "component: deleted [" + name + "]" << std::endl;
    }
};

/*
    entity
*/

class Entity
{
public:
    Entity(Mesh* mesh, Texture* texture, Shader* shader) {
        m_transform = new Transform();
        m_components = new ComponentManager(this);

        m_mesh = mesh;
        m_texture = texture;
        m_shader = shader;
    }
    
    ~Entity() {
        delete m_transform;
        delete m_components;
    }

    void update() {
        components()->update();
    }

    ComponentManager* components() { return m_components; }
    Transform* transform() { return m_transform; }

    Mesh* mesh() { return m_mesh; }
    Texture* texture() { return m_texture; }
    Shader* shader() { return m_shader; }
    
private:
    ComponentManager* m_components; 
    Transform* m_transform;

    Mesh* m_mesh;
    Texture* m_texture;
    Shader* m_shader;
};

/*
    entity manager
*/

class EntityManager
{
public:
    EntityManager() {

    }

    ~EntityManager() {
        TimeProfiler::begin();

        auto batch = m_entities_batch.begin();
        while (batch != m_entities_batch.end()) {
            delete_batch(batch->first, batch->second);
            batch++;
        }

        auto entity = m_entities.begin();
        while (entity != m_entities.end()) {
            delete_entity(entity->first, entity->second);
            entity++;
        }

        TimeProfiler::end("entity remove");
    }

    void update()
    {
        auto batch = m_entities_batch.begin();
        while (batch != m_entities_batch.end()) {
            for (auto entity : *batch->second) {
                entity->update();
            }
            batch++;
        }

        auto entity = m_entities.begin();
        while (entity != m_entities.end()) {
            entity->second->update();
            entity++;
        }
    }

    void add_entity(std::string&& name, Mesh* mesh, Texture* texture, Shader* shader)
    {
        auto it = m_entities.find(name);

        if (it != m_entities.end())
            throw std::runtime_error("error: entity already exist [" + name + "]");

        m_entities.emplace(name, new Entity(mesh, texture, shader));
        std::cout << "entity: added [" + name + "]" << std::endl;
    }

    void add_batch(std::string&& name)
    {
        auto it = m_entities_batch.find(name);

        if (it != m_entities_batch.end())
            throw std::runtime_error("error: entity batch already exist [" + name + "]");

        m_entities_batch.emplace(name, new std::vector<Entity*>());
        std::cout << "entity batch: added [" + name + "]" << std::endl;
    }

    Entity* get_entity(std::string&& name)
    {
        auto it = m_entities.find(name);

        if (it == m_entities.end())
            throw std::runtime_error("error: entity doesn't exist [" + name + "]");

        return it->second; 
    }

    std::vector<Entity*>* get_batch(std::string&& name)
    {
        auto it = m_entities_batch.find(name);

	    if (it == m_entities_batch.end())
		    throw std::runtime_error("error: entity batch doesn't exist [" + name + "]");
	    
        return it->second;
    }

    void remove_entity(std::string&& name)
    {
        auto it = m_entities.find(name);

        if (it == m_entities.end())
            throw std::runtime_error("error: (remove) entity doesn't exist [" + name + "]");

        delete_entity(name, it->second);
        m_entities.erase(it);
    }

    void remove_batch(std::string&& name)
    {
        auto it = m_entities_batch.find(name);

        if (it == m_entities_batch.end())
            throw std::runtime_error("error: (remove) entity batch doesn't exist [" + name + "]");

        delete_batch(name, it->second);
        m_entities_batch.erase(it);
    }

    const std::unordered_map<std::string, Entity*>& entities() { return m_entities; }
    const std::unordered_map<std::string, std::vector<Entity*>*>& entities_batch() { return m_entities_batch; };

private:
    std::unordered_map<std::string, Entity*> m_entities;
    std::unordered_map<std::string, std::vector<Entity*>*> m_entities_batch;

    void delete_entity(std::string name, Entity* entity)
    {
        delete entity;
        std::cout << "entity: removed [" + name + "]" << std::endl;
    }

    void delete_batch(std::string name, std::vector<Entity*>* batch)
    {
        std::cout << "entity batch: " << batch->size() << " removed [" + name + "]" << std::endl;
        auto it = batch->begin();
        while (it != batch->end()) {
            delete *it;
            it++;
        }

        batch->clear();
        batch->shrink_to_fit();        
    }

};

#endif //ECS_H
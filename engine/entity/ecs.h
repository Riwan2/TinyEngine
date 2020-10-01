#ifndef ECS_H
#define ECS_H

#include <list>
#include <string>
#include <iostream>
#include <typeinfo>

class Entity;

/*
    component
*/

class Component
{
public:
    Component() {}
    virtual ~Component() {}

protected:
    Entity* entity() { return m_entity; }

private:
    Entity* m_entity;
};

class BasicComponent : public Component
{

};

class PowerComponent : public Component
{

};

/*
    component manager
*/

class ComponentManager
{
public:
    ComponentManager() {}

    ~ComponentManager()
    {
        for (auto component : m_components) {
            std::string name = typeid(*component).name();
            delete_component(component, std::move(name));
        }
    }

    template <class T>
    void add_component(T *component)
    {
        std::string name = typeid(T).name();

        for (auto component : m_components) {
            if (dynamic_cast<T *>(component)) {
                throw std::runtime_error("error: component already exist [" + name + "]");
            }
        }

        std::cout << "component: added [" + name + "]" << std::endl;
        m_components.push_back(component);
    }

    template <class T>
    Component *get_component()
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
    void remove_component()
    {
        std::string name = typeid(T).name();
        Component *target = get_component<T>();

        m_components.remove(target);
        delete_component(target, std::move(name));
    }

private:
    std::list<Component *> m_components;

    void delete_component(Component *comp, std::string &&name)
    {
        delete comp;
        std::cout << "component: deleted [" + name + "]" << std::endl;
    }
};

/*
    entity
*/

class Entity
{
public:
    Entity() {}
    ~Entity() {}

protected:
    ComponentManager* components() { return m_components; }

private:
    ComponentManager* m_components;
};

#endif //ECS_H
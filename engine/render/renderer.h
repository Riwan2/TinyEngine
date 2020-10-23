#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

#include "../entity/ecs.h"
#include "../camera/camera.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void render(Entity* entity);
    void render_batch(std::vector<Entity*>* batch);
    
    void set_camera(Camera* camera);

private:
    Camera* m_camera;

    void update_transform(Entity* entity);
};

#endif //RENDERER_H
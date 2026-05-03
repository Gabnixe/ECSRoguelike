#pragma once

#include "raylib.h"

#include "../core/System.hpp"
#include "../core/ECS.hpp"

#include "../components/VelocityComponent.hpp"
#include "../components/Transform2DComponent.hpp"

extern ECS ecs;

class MoveSystem : public System
{
public:
    void Update(float deltaTime)
    {
        for (auto const& entity : entities)
	    {
            auto& transform2DComponent = ecs.GetComponent<Transform2DComponent>(entity);
		    auto const& velocityComponent = ecs.GetComponent<VelocityComponent>(entity);

            transform2DComponent.position.x += (velocityComponent.velocity.x * deltaTime);
            transform2DComponent.position.y += (velocityComponent.velocity.y * deltaTime);
        }
    }
};
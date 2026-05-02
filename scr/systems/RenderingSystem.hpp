#pragma once

#include "raylib.h"

#include "../core/System.hpp"
#include "../core/ECS.hpp"

#include "../components/ColorComponent.hpp"
#include "../components/Transform2DComponent.hpp"

extern ECS ecs;

class RenderingSystem : public System
{
public:
    void Draw()
    {
        ClearBackground(RAYWHITE);

        for (auto const& entity : entities)
	    {
            auto const& transform2DComponent = ecs.GetComponent<Transform2DComponent>(entity);
		    auto const& colorComponent = ecs.GetComponent<ColorComponent>(entity);

            DrawCircleV(transform2DComponent.position, transform2DComponent.scale, colorComponent.color);
        }
    }
};

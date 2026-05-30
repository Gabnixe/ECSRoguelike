#include "raylib.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Debug.hpp"

#include "core/ECS.hpp"

#include <entt/entt.hpp>

#include "systems/RenderingSystem.hpp"
#include "systems/MoveSystem.hpp"

const std::string windowTitle = "ECSRoguelike";
const int screenWidth = 800;
const int screenHeight = 400;

ECS ecs;

void Update()
{
    AddFPSToWindowTitle(windowTitle);
}

void Draw()
{
    ClearBackground(RAYWHITE);
}

struct position {
    float x;
    float y;
};

struct velocity {
    float dx;
    float dy;
};

struct size {
    float radius;
};

struct color {
    Color color;
};

void ECSUpdate(entt::registry &registry){
    Update();

    auto view = registry.view<position, const velocity>();

    // use a callback
    view.each([](auto &pos, const auto &vel) 
    {
        pos.x += vel.dx * GetFrameTime();
        pos.y += vel.dy * GetFrameTime();
    });

    BeginDrawing();
    Draw();
    auto view2 = registry.view<const position, const size, const color>();
    // use a callback
    view2.each([](const auto &pos, const auto &size, const auto &color) 
    {
        DrawCircleV(Vector2{pos.x, pos.y}, size.radius, color.color);
    });
    EndDrawing();
}

int main()
{
    //Window Config
    SetConfigFlags(FLAG_WINDOW_HIGHDPI | /*FLAG_VSYNC_HINT |*/ FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, windowTitle.c_str());
    //SetTargetFPS(60);

    //InHouseECS 310

    ecs.Init();
    ecs.RegisterComponent<Transform2DComponent>();
    ecs.RegisterComponent<ColorComponent>();
    ecs.RegisterComponent<VelocityComponent>();

    auto renderingSystem = ecs.RegisterSystem<RenderingSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<ColorComponent>());
        signature.set(ecs.GetComponentType<Transform2DComponent>());
        ecs.SetSystemSignature<RenderingSystem>(signature);
    }

    auto moveSystem = ecs.RegisterSystem<MoveSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<VelocityComponent>());
        signature.set(ecs.GetComponentType<Transform2DComponent>());
        ecs.SetSystemSignature<MoveSystem>(signature);
    }

    //Spawn a bunch of moving circles
    for(int i = 0; i < MAX_ENTITIES; ++i)
    {
        Entity testEntity = ecs.CreateEntity();
        ecs.AddComponent(
            testEntity, 
            Transform2DComponent
            {
                .position = Vector2{(float)GetRandomValue(0,screenWidth), (float)GetRandomValue(0,screenHeight)},
                .rotation = 0,
                .scale = GetRandomValue(0,100)
            });
        ecs.AddComponent(
            testEntity, 
            ColorComponent
            {
                .color = 
                {
                    .r = ((unsigned char)GetRandomValue(0,255)),
                    .g = ((unsigned char)GetRandomValue(0,255)),
                    .b = ((unsigned char)GetRandomValue(0,255)),
                    .a = 255
                }
            });
        ecs.AddComponent(
            testEntity,
            VelocityComponent
            {
                .velocity = Vector2{(float)GetRandomValue(-100,100), (float)GetRandomValue(-100,100)}
            });
    }

    //Game Loop
	while (!WindowShouldClose())
	{
        Update();
        moveSystem->Update(GetFrameTime());
        BeginDrawing();
            renderingSystem->Draw();
            Draw();
        EndDrawing();
	}

    //EnTT 290

    /*
    entt::registry registry;

    for(auto i = 0; i < MAX_ENTITIES; ++i) 
    {
        const auto entity = registry.create();
        registry.emplace<position>(entity, (float)GetRandomValue(0,screenWidth), (float)GetRandomValue(0,screenHeight));
        registry.emplace<velocity>(entity, (float)GetRandomValue(-100,100), (float)GetRandomValue(-100,100));
        registry.emplace<size>(entity, (float)GetRandomValue(0,100));
        registry.emplace<color>(entity, Color                
                {
                    .r = ((unsigned char)GetRandomValue(0,255)),
                    .g = ((unsigned char)GetRandomValue(0,255)),
                    .b = ((unsigned char)GetRandomValue(0,255)),
                    .a = 255
                });
    }

    //Game Loop
	while (!WindowShouldClose())
	{
        ECSUpdate(registry);
        //Update();
        //BeginDrawing();
            //Draw();
        //EndDrawing();
	}
    */

    //NO ECS COMPARAISON TEST 360


    /*
    class Circle
    {
    public:
        Vector2 position;
        float scale;
        Color color;
        Vector2 velocity;

        void Update(float deltaTime)
        {
            position.x += (velocity.x * deltaTime);
            position.y += (velocity.y * deltaTime);
        }

        void Draw()
        {
            DrawCircleV(position, scale, color);
        }
    };

    std::vector<std::shared_ptr<Circle>> circles(MAX_ENTITIES);
    for(int i = 0; i < MAX_ENTITIES; ++i)
    {
        std::shared_ptr<Circle> circle = std::make_shared<Circle>();
        circles[i] = circle;
        circle->position = Vector2{(float)GetRandomValue(0,screenWidth), (float)GetRandomValue(0,screenHeight)},
        circle->scale = GetRandomValue(0,100);
        circle->color = 
            {
                .r = ((unsigned char)GetRandomValue(0,255)),
                .g = ((unsigned char)GetRandomValue(0,255)),
                .b = ((unsigned char)GetRandomValue(0,255)),
                .a = 255
            };
        circle->velocity = Vector2{(float)GetRandomValue(-100,100), (float)GetRandomValue(-100,100)};
    }

    while (!WindowShouldClose())
	{
        Update();
        for(auto circle : circles)
        {
            circle->Update(GetFrameTime());
        }
        BeginDrawing();
            for(auto circle : circles)
            {
                circle->Draw();
            }
            Draw();
        EndDrawing();
	}*/

    //Close Game
	CloseWindow();
	return 0;
}
#include "raylib.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Debug.hpp"

#include "core/ECS.hpp"

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

int main()
{
    //Window Config
    SetConfigFlags(FLAG_WINDOW_HIGHDPI | /*FLAG_VSYNC_HINT |*/ FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, windowTitle.c_str());
    //SetTargetFPS(60);

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

    //Close Game
	CloseWindow();
	return 0;
}
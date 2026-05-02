#include "raylib.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <memory>

#include "Debug.hpp"

#include "core/ECS.hpp"

#include "systems/RenderingSystem.hpp"

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

    auto renderingSystem = ecs.RegisterSystem<RenderingSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<ColorComponent>());
        signature.set(ecs.GetComponentType<Transform2DComponent>());
        ecs.SetSystemSignature<RenderingSystem>(signature);
    }

    Entity testEntity = ecs.CreateEntity();
    ecs.AddComponent(
    testEntity, 
    Transform2DComponent
    {
        .position = Vector2{100, 100},
        .rotation = 0,
        .scale = 100
    });
    ecs.AddComponent(
    testEntity, 
    ColorComponent
    {
        .color = RED
    });

    //Game Loop
	while (!WindowShouldClose())
	{
        Update();
        BeginDrawing();
            renderingSystem->Draw();
            Draw();
        EndDrawing();
	}

    //Close Game
	CloseWindow();
	return 0;
}
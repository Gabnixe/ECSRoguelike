#include "raylib.h"
#include <stdio.h>

const int screenWidth = 800;
const int screenHeight = 400;

void Update()
{
    
}

void Draw()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        char buffer[100];
        sprintf(buffer, "%.0f FPS", 1 / GetFrameTime());
        DrawText(buffer, 0, 0, 20, BLACK);
    EndDrawing();
}

int main()
{
    //Window Config
    SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "ECSRoguelike");
    SetTargetFPS(60);

    //Game Loop
	while (!WindowShouldClose())
	{
        Update();
        Draw();
	}

    //Close Game
	CloseWindow();
	return 0;
}
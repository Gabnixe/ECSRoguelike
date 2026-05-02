#include "raylib.h"
#include <string>

void AddFPSToWindowTitle(std::string windowTitle)
{
    int fps = 1 / GetFrameTime();
    SetWindowTitle((windowTitle + " (FPS: " + std::to_string(fps) + ")").c_str());
}
#include "raylib.h"
#include "gui.hpp"

#include <cstdlib> 

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        pathToAudio = argv[1];
        isPlaying = true;
        SetWindowTitle(("FAudio - " + std::string(argv[1])).c_str());
    }
    InitWindow(winW,winH, "FAudio");

    InitAudioDevice();
    rlImGuiSetup(true);
    SetTargetFPS(244);

    // Main 
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        BeginDrawing();
        ClearBackground(BLACK);

        

        if (isPlaying && !IsMusicStreamPlaying(music))
        {
            PlayMusicStream(music);
        }
        else if (!isPlaying && IsMusicStreamPlaying(music))
        {
            PauseMusicStream(music);
        }


        UpdateRayGui();
        UpdateImGui();

        EndDrawing();
    }

    CloseAudioDevice();

    rlImGuiShutdown();	
    CloseWindow();

    return 0;
}
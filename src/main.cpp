#include "raylib.h"
#include "gui.hpp"

#include <cstdlib> 

int main(int argc, char* argv[])
{
    InitWindow(winW,winH, "FAudio");

    InitAudioDevice();
    rlImGuiSetup(true);
    SetTargetFPS(244);

    if (argc > 1)
    {
        std::cout << "\n\n\n\nARG[1] ======================================== " << argv[1] << "\n";
        pathToAudio = std::string(argv[1]);
        music = ConvertAndLoadMusic(pathToAudio);
        
        isPlaying = true;
        SetWindowTitle(("FAudio - " + std::string(argv[1])).c_str());
    }
    

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
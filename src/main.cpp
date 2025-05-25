#include "raylib.h"
#include "gui.hpp"

#include <cstdlib> 

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    InitWindow(winW,winH, "FAudio");

    InitAudioDevice();
    rlImGuiSetup(true);
    SetTargetFPS(244);

    if (argc > 1)
    {
        std::cout << "\n\n\n\nARG[1] ======================================== " << argv[1] << "\n";
        exeDir = std::filesystem::path(argv[0]).parent_path();
        pathToAudio = std::string(argv[1]);
        music = ConvertAndLoadMusic(pathToAudio);
        musicTime = GetMusicTimeLength(music);
        minutes = ((int)musicTime % 3600) / 60;
        seconds = (int)musicTime % 60;

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
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

extern std::string pathToAudio;
extern Music music;
extern float volume;
extern float musicTime;
extern int minutes;
extern int seconds;
extern float musicCurrentTime;
extern int minutesListened;
extern int secondsListened;
extern float musicLengthStopped;
extern int winW;
extern int winH;
extern bool isPlaying;
extern Music ConvertAndLoadMusic(const std::string& originalPath);
extern void UpdateRayGui();
extern void UpdateImGui();
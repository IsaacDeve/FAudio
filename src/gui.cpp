#include "gui.hpp"

std::string pathToAudio = "";

Music music;

float volume = 50.0f;

float musicTime = 0.0f;
int minutes = 0;
int seconds = 0;
float musicCurrentTime = 0.0f;
int minutesListened = 0.0f;
int secondsListened = 0.0f;


float musicLengthStopped = 0.0f;


int winW = 400;
int winH = 220;

bool isPlaying = false;


Music ConvertAndLoadMusic(const std::string& originalPath) {
    try
    {
        namespace fs = std::filesystem;

        fs::path ffmpegExe = fs::current_path() / "ffmpeg" / "bin" / "ffmpeg.exe";
        fs::path tempWav = fs::temp_directory_path() / "faudio_temp.wav";
        fs::path batFile = fs::temp_directory_path() / "faudio_convert.bat";

        if (fs::exists(tempWav)) {}

        if (!fs::exists(originalPath)) {
            return {};
        }

        std::ofstream bat(batFile);
        bat << "\"" << ffmpegExe.string() << "\" -y -i \"" << originalPath << "\" -f wav \"" << tempWav.string() << "\"\n";
        bat.close();

        int result = system(batFile.string().c_str());
        fs::remove(batFile);

        if (result != 0 || !fs::exists(tempWav)) {
            std::cerr << "ffmpeg cant blyat: " << result << "\n";
            return {};
        }

        return LoadMusicStream(tempWav.string().c_str());
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return {};
    }

}




void UpdateRayGui()
{
    musicCurrentTime = GetMusicTimePlayed(music);

    minutesListened = ((int)musicCurrentTime % 3600) / 60;
    secondsListened = (int)musicCurrentTime % 60;

    if (IsFileDropped())
    {
        FilePathList droppedFiles = LoadDroppedFiles();
        if (droppedFiles.count > 0)
        {
            pathToAudio = droppedFiles.paths[0];
            UnloadMusicStream(music);
            music = ConvertAndLoadMusic(pathToAudio);
            musicTime = GetMusicTimeLength(music);
            minutes = ((int)musicTime % 3600) / 60;
            seconds = (int)musicTime % 60;

            isPlaying = true;

            SetWindowTitle(("FAudio - " + std::string(droppedFiles.paths[0])).c_str());
        }
        UnloadDroppedFiles(droppedFiles);
    }
}

void UpdateImGui()
{
    rlImGuiBegin();

    ImGui::SetNextWindowPos(ImVec2(0,0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(float(winW),float(winH)-50), ImGuiCond_Always );
    if (ImGui::Begin("Audio"), nullptr, ImGuiWindowFlags_NoCollapse)
    {
        ImGui::SliderFloat("Volume", &volume, 0.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
        SetMusicVolume(music, volume/100.0f);
        ImGui::SameLine();
        if (ImGui::Button(isPlaying ? "Stop" : "Play"))
        {
            isPlaying = !isPlaying;
        }
        ImGui::Text("Duration: %02d:%02d out of %02d:%02d", minutesListened, secondsListened, minutes, seconds);
    }
    ImGui::SetNextWindowPos(ImVec2(0,float(winH)-70), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(float(winW),90), ImGuiCond_Always );                              

    if (ImGui::Begin("Audio Length", nullptr, ImGuiWindowFlags_NoCollapse));
    {
        ImGui::Text("Duration: %02d:%02d / %02d:%02d", minutesListened, secondsListened, minutes, seconds);
        if (ImGui::SliderFloat("Time", &musicCurrentTime, 0.0f, musicTime, "%.2f", ImGuiSliderFlags_AlwaysClamp))
        {
            SeekMusicStream(music, musicCurrentTime);
        }
        ImGui::End();
    }

    //CONTROLS
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
    {
        isPlaying = !isPlaying;
        musicLengthStopped = musicCurrentTime;
        if (isPlaying)
        {
            PlayMusicStream(music);
        }
        else
        {
            StopMusicStream(music);
            SeekMusicStream(music, musicLengthStopped);
        }
    }


    ImGui::End();
    rlImGuiEnd();
}   

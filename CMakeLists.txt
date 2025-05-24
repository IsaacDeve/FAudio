cmake_minimum_required(VERSION 3.10)
project(FAudio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

if (UNIX)
    set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/imgui)
include_directories(${CMAKE_SOURCE_DIR}/include/rlImGui)
#include_directories(${CMAKE_SOURCE_DIR}/third_party/discordsdk)

link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(FAudio 
    src/main.cpp
    src/gui.cpp

    ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui.cpp 
    ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui_draw.cpp 
    ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui_demo.cpp 
    ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui_tables.cpp 
    ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui_widgets.cpp 
    ${CMAKE_SOURCE_DIR}/include/rlImGui/rlImGui.cpp
)


if (WIN32)
    target_link_libraries(FAudio
    ${CMAKE_SOURCE_DIR}/lib/raylib.lib opengl32 gdi32 winmm user32
    #${CMAKE_SOURCE_DIR}/third_party/discordsdk/lib/x86_64/discord_game_sdk.dll.lib
    )
else()
    target_link_libraries(FAudio raylib m dl pthread GL)
endif()
cmake_minimum_required(VERSION 3.10)
project(FAudio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/imgui)
include_directories(${CMAKE_SOURCE_DIR}/include/rlImGui)

link_directories(${CMAKE_SOURCE_DIR}/lib)

# Executable
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

add_custom_command(TARGET FAudio POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/ffmpeg"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/ffmpeg"
)

add_custom_command(TARGET FAudio POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_SOURCE_DIR}/credits.txt"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/credits.txt"
)

if (WIN32)
    target_link_libraries(FAudio
        ${CMAKE_SOURCE_DIR}/lib/raylib.lib
        opengl32 gdi32 winmm user32
    )
else()
    target_link_libraries(FAudio raylib m dl pthread GL)
endif()

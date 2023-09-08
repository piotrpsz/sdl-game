cmake_minimum_required(VERSION 3.26)
project(sdl_game)

set(CMAKE_CXX_STANDARD 17)
include_directories("/usr/local/include")
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED CONFIG REQUIRED COMPONENTS SDL3_image-shared)

add_executable(sdl_game main.cpp
        game.cpp
        game.h
        drawer.cpp
        drawer.h
        drawer.cpp
        drawer.h
        types.h
)

target_link_libraries(sdl_game PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

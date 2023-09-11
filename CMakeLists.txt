cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)

project(sdl_game)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED CONFIG REQUIRED COMPONENTS SDL3_image-shared)
find_package(SDL3_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL3_ttf-shared)

add_executable(sdl_game main.cpp
        game.cpp
        game.h
        drawer.cpp
        drawer.h
        drawer.cpp
        drawer.h
        types.h
        font.cpp
        font.h
        actor/ball.cpp
        actor/ball.h
        shared.cpp
        shared.h
)

target_link_libraries(sdl_game PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
)

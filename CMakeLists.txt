cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

project(sdl_game)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED CONFIG REQUIRED COMPONENTS SDL3_image-shared)
find_package(SDL3_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL3_ttf-shared)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

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
        actor/paddle.cpp
        actor/paddle.h
        actor/actor.cpp
        actor/actor.h
        actor/wall.cpp
        actor/wall.h
        actor/label.cpp
        actor/label.h
)

target_link_libraries(sdl_game PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
)

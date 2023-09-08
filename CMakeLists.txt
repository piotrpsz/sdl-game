cmake_minimum_required(VERSION 3.26)
project(sdl_test)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-03")

set(SDL_INCLUDE_DIR C:/Users/user/Projects/SDL/include)
set(SDL_LIBRARY C:/Users/user/Projects/SDL/VisualC/x64/Release/SDL3.lib)
include_directories(${SDL_INCLUDE_DIR})

#find_package(SDL REQUIRED)

add_executable(sdl_test main.cpp
        game.cpp
        game.h
        drawer.cpp
        drawer.h
        drawer.cpp
        drawer.h
        types.h)
target_link_libraries(sdl_test ${SDL_LIBRARY})

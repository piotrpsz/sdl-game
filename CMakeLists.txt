cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

project(sdl_game)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED CONFIG REQUIRED COMPONENTS SDL3_image-shared)
find_package(SDL3_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL3_ttf-shared)

# ------- FMOD --------------------------------------------

set(FMOD_STUDIO_DIR "/Users/piotr/Projects/cpp/FMOD/api/studio")
set(FMOD_CORE_DIR "/Users/piotr/Projects/cpp/FMOD/api/core")

set(FMOD_STUDIO_DLL_LIB "${FMOD_STUDIO_DIR}/lib/libfmodstudio.dylib")
set(FMOD_STUDIO_DLL_LIB_L "${FMOD_STUDIO_DIR}/lib/libfmodstudioL.dylib")
set(FMOD_CORE_DLL_LIB "${FMOD_CORE_DIR}/lib/libfmod.dylib")
set(FMOD_CORE_DLL_LIB_L "${FMOD_CORE_DIR}/lib/libfmodL.dylib")

add_library(fmod_studio SHARED IMPORTED)
add_library(fmod_studio_l SHARED IMPORTED)
add_library(fmod_core SHARED IMPORTED)

add_library(fmod_core_l SHARED IMPORTED)

set_property(TARGET fmod_studio PROPERTY IMPORTED_LOCATION "${FMOD_STUDIO_DLL_LIB}")
set_property(TARGET fmod_studio_l PROPERTY IMPORTED_LOCATION "${FMOD_STUDIO_DLL_LIB_L}")
set_property(TARGET fmod_studio PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${FMOD_STUDIO_DIR}/inc" "${FMOD_CORE_DIR}/inc")
set_property(TARGET fmod_studio_l PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${FMOD_STUDIO_DIR}/inc")

set_property(TARGET fmod_core PROPERTY IMPORTED_LOCATION "${FMOD_CORE_DLL_LIB}")
set_property(TARGET fmod_core_l PROPERTY IMPORTED_LOCATION "${FMOD_CORE_DLL_LIB_L}")
set_property(TARGET fmod_core PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${FMOD_CORE_DIR}/inc")
set_property(TARGET fmod_core_l PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${FMOD_CORE_DIR}/inc")

# ------- END OF FMODE ------------------------------------

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
        fmod/audio.cpp
        fmod/audio.h
        fmod/sound_event.cpp
        fmod/sound_event.h
        math/math.h
        math/vec2.cpp math/vec2.h
        math/vec3.cpp math/vec3.h
        math/matrix4.cpp
        math/matrix4.h
        math/matrix3.cpp
        math/matrix3.h
        math/quaternion.cpp
        math/quaternion.h
)

target_link_libraries(sdl_game PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        fmod_studio fmod_studio_l
        fmod_core fmod_core_l
)

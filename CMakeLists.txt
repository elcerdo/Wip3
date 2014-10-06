project(wip3)
cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED SDL2 sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image sdl2_image)
include_directories(${SDL2IMAGE_INCLUDE_DIRS})

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
link_directories(${GLM_LIBRARY_DIRS})
add_definitions(${GLM_DEFINITIONS})

message(STATUS "GLM_FOUND ${GLM_FOUND}")
message(STATUS "SDL2_FOUND ${SDL2_FOUND}")
message(STATUS "SDL2IMAGE_FOUND ${SDL2IMAGE_FOUND}")

add_executable(game
    Camera.cpp
    Cube.cpp
    Input.cpp
    Physics.cpp
    SceneOpenGL.cpp
    Shader.cpp
    Ship.cpp
    Texture.cpp
    main.cpp)

target_link_libraries(game
    ${SDL2_LIBRARIES}
    ${GLM_LIBRARIES})


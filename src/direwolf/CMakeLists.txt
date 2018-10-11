project(DireWolf DESCRIPTION "Device Independent Rendering Engine with Other Lively Features")
cmake_minimum_required(VERSION 3.9.2)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(DIREWOLF_BUILD_EXAMPLES OFF)

if (DIREWOLF_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (BUILD_SHARED_LIBS)
    add_library(direwolf SHARED src/renderengine.cpp src/opengl/renderer_ogl.cpp)
else()
    add_library(direwolf STATIC src/renderengine.cpp src/opengl/renderer_ogl.cpp)
endif()

target_include_directories(direwolf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)

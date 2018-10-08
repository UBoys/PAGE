project(PGFX DESCRIPTION "Renderer backend for the PAGE engine")
cmake_minimum_required(VERSION 3.9.2)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(PGFX_BUILD_EXAMPLES OFF)

if (PGFX_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (BUILD_SHARED_LIBS)
    add_library(pgfx SHARED src/pgfx.cpp)
else()
    add_library(pgfx STATIC src/pgfx.cpp)
endif()

target_include_directories(pgfx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include src)

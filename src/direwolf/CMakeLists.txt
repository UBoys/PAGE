project(DireWolf DESCRIPTION "Device Independent Rendering Engine with Other Lively Features")
cmake_minimum_required(VERSION 3.9.2)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(DIREWOLF_BUILD_EXAMPLES OFF)
option(DIREWOLF_BUILD_OPENGL_RENDERER ON)

if (DIREWOLF_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

add_definitions(-DGLEW_STATIC)
add_subdirectory(ext/glew-cmake)

set(SOURCE_FILES
	src/renderengine.cpp
	src/common/logger.cpp
	src/opengl/renderer_ogl.cpp
	src/opengl/platform/rendercontext_win.cpp
	src/opengl/platform/rendercontext_osx.mm
)

if (BUILD_SHARED_LIBS)
	add_library(direwolf SHARED ${SOURCE_FILES})
else()
    add_library(direwolf STATIC ${SOURCE_FILES})
endif()

target_include_directories(
	direwolf
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/ext/glew-cmake/include
	${CMAKE_CURRENT_SOURCE_DIR}/ext/glew-cmake/src
)
target_link_libraries(direwolf libglew_static)

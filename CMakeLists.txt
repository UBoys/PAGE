project(PAGE)
cmake_minimum_required(VERSION 3.12)

# Compilation flags
if(MSVC)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /std:c++17")
else(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17")
endif(MSVC)

file(GLOB_RECURSE PROJECT_CORE src/core/*.cpp src/core/*.h)
file(GLOB_RECURSE PROJECT_RENDERER src/renderer/*.cpp src/renderer/*.h)
file(GLOB_RECURSE PROJECT_EXAMPLES src/examples/*.cpp src/examples/*.h)

# IDE groups
source_group("Core" FILES ${PROJECT_CORE})
source_group("Renderer" FILES ${PROJECT_RENDERER})
source_group("Examples" FILES ${PROJECT_EXAMPLES})

# Choose the right startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${PROJECT_CORE} ${PROJECT_RENDERER} ${PROJECT_EXAMPLES})

include_directories(src/)

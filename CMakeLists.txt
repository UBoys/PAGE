cmake_minimum_required(VERSION 3.9.2)
project(PAGE)
message("Creating project PAGE")

# Compilation flags
if(MSVC)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /std:c++17")
else(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17")
endif(MSVC)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(PAGE_GLFW_ENABLED "Should we include GLFW?" OFF)

# DireWolf - TODO Move to submodule
add_subdirectory(src/direwolf)

file(GLOB_RECURSE PROJECT_DISPLAY src/display/*.cpp src/display/*.h)
file(GLOB_RECURSE PROJECT_CORE src/core/*.cpp src/core/*.h)
file(GLOB_RECURSE PROJECT_EXAMPLES src/examples/*.cpp src/examples/*.h)

# IDE groups
source_group("Display" FILES ${PROJECT_DISPLAY})
source_group("Core" FILES ${PROJECT_CORE})
source_group("Examples" FILES ${PROJECT_EXAMPLES})

# Choose the right startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${PROJECT_DISPLAY} ${PROJECT_CORE} ${PROJECT_EXAMPLES})

target_include_directories(${PROJECT_NAME} PUBLIC src/ direwolf/include/)

target_link_libraries(${PROJECT_NAME} direwolf)

# Glfw stuff
if (PAGE_GLFW_ENABLED)
  option(GLFW_BUILD_DOCS OFF)
  option(GLFW_BUILD_EXAMPLES OFF)
  option(GLFW_BUILD_TESTS OFF)
  add_subdirectory(ext/glfw)
  target_link_libraries(${PROJECT_NAME} glfw)
endif(PAGE_GLFW_ENABLED)

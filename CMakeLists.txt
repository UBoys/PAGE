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

file(GLOB_RECURSE PROJECT_CORE src/core/*.cpp src/core/*.h)
file(GLOB_RECURSE PROJECT_RENDERER src/renderer/*.cpp src/renderer/*.h src/renderer/*.inl)
file(GLOB_RECURSE PROJECT_EXAMPLES src/examples/*.cpp src/examples/*.h)

# IDE groups
source_group("Core" FILES ${PROJECT_CORE})
source_group("Renderer" FILES ${PROJECT_RENDERER})
source_group("Examples" FILES ${PROJECT_EXAMPLES})

# Choose the right startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${PROJECT_CORE} ${PROJECT_RENDERER} ${PROJECT_EXAMPLES})

include_directories(src/)

# Include link_libraries
option(PAGE_GLFW_ENABLED "Should we use GLFW? (TODO: Implement this.. just added for grouping in CMAKE UI atm ;)" ON)

option(PAGE_VULKAN_ENABLED "Should we use the vulkan API?")
if (PAGE_VULKAN_ENABLED)

	add_compile_definitions(VK_NO_PROTOTYPES)

endif (PAGE_VULKAN_ENABLED)

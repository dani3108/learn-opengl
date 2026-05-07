cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

# Third party libraries
add_subdirectory("lib/glad")            # OpenGL loader
add_subdirectory("lib/glfw-3.4")        # Creating windows

project(LearnOpenGL VERSION 0.1.0 LANGUAGES C CXX)

# Before add_executable
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${CMAKE_PROJECT_NAME} src/1_getting_started/hellowindow.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} glfw glad)

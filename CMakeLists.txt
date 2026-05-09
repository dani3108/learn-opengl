cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)
project(LearnOpenGL VERSION 0.1.0 LANGUAGES C CXX)

# =========================================
# Global config
# =========================================

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# =========================================
# Third party libraries
# =========================================

# OpenGL package
find_package(OpenGL REQUIRED)

add_subdirectory("lib/glad")            # OpenGL loader
add_subdirectory("lib/glfw-3.4")        # Creating windows

# =========================================
# OpenGL Chapters
# =========================================

add_subdirectory(src/chapter_1_getting_started)
# add_subdirectory(src/chapter_2_lighting)

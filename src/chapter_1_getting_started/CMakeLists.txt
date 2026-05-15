# =========================================
# Compile flags
# =========================================

if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
    )
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(
            -Wconditional-uninitialized
        )
    endif()
endif()

# =========================================
# 1. Hello Window
# =========================================

add_executable(
    hello_window
    lesson_1_hello_window/hello_window.cpp
)

target_link_libraries(
    hello_window
    glfw
    glad
    OpenGL::GL
)

# =========================================
# 2. Hello Triangle
# =========================================

add_executable(
    hello_triangle
    lesson_2_hello_triangle/hello_triangle.cpp
)

target_link_libraries(
    hello_triangle 
    glfw 
    glad 
    OpenGL::GL
)

# =========================================
# 2.1 Hello Triangle Indexed
# =========================================

add_executable(
    hello_triangle_indexed
    lesson_2_hello_triangle/hello_triangle_indexed.cpp
)

target_link_libraries(
    hello_triangle_indexed
    glfw 
    glad 
    OpenGL::GL
)

# =========================================
# 2.2 Hello Triangle Exercise 1
# =========================================

add_executable(
    hello_triangle_exercise_1
    lesson_2_hello_triangle/hello_triangle_exercise_1.cpp
)

target_link_libraries(
    hello_triangle_exercise_1
    glfw 
    glad 
    OpenGL::GL
)

# =========================================
# 2.3 Hello Triangle Exercise 2
# =========================================

add_executable(
    hello_triangle_exercise_2
    lesson_2_hello_triangle/hello_triangle_exercise_2.cpp
)

target_link_libraries(
    hello_triangle_exercise_2
    glfw 
    glad 
    OpenGL::GL
)



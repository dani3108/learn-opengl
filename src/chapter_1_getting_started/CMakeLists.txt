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
# Lessons
# =========================================

# 1. Hello Window
add_demo(hello_window lesson_1_hello_window/hello_window.cpp)
# 2. Hello Triangle
add_demo(hello_triangle lesson_2_hello_triangle/hello_triangle.cpp)
# 2.1 Hello Triangle Indexed
add_demo(hello_triangle_indexed lesson_2_hello_triangle/hello_triangle_indexed.cpp)
# 2.2 Hello Triangle Exercise 1
add_demo(hello_triangle_exercise_1 lesson_2_hello_triangle/hello_triangle_exercise_1.cpp)
# 2.3 Hello Triangle Exercise 2
add_demo(hello_triangle_exercise_2 lesson_2_hello_triangle/hello_triangle_exercise_2.cpp)
# 2.4 Hello Triangle Exercise 3
add_demo(hello_triangle_exercise_3 lesson_2_hello_triangle/hello_triangle_exercise_3.cpp)


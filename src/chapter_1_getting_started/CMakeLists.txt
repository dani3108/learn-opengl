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

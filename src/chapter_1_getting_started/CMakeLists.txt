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

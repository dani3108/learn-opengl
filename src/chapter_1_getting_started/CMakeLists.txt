# =========================================
# Compile flags
# =========================================

# We don't want these settings to apply to third party libraries
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
add_subdirectory(lesson_1_hello_window)
# 2. Hello Triangle
add_subdirectory(lesson_2_hello_triangle)
# 3. Shaders
add_subdirectory(lesson_3_shaders)


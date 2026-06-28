cmake_minimum_required(VERSION 3.24)

project(openGl_figures
    VERSION 1.0.0
    DESCRIPTION "2D geometric figures in OpenGL (OOP, PIMPL, no Qt)"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# GLFW: системный, иначе через FetchContent.
find_package(glfw3 3.3 QUIET)
if(NOT glfw3_FOUND)
    include(FetchContent)
    FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
        GIT_SHALLOW TRUE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(glfw)
endif()

if(MSVC)
    set(FIG_WARNINGS /W4)
else()
    set(FIG_WARNINGS -Wall -Wextra -Wpedantic)
endif()

# core: геометрия + сцена, без OpenGL (тестируется отдельно).
add_library(fig_core
    src/geometry/Circle.cpp
    src/geometry/Rectangle.cpp
    src/geometry/Triangle.cpp
    src/geometry/RegularPolygon.cpp
    src/geometry/ShapeFactory.cpp
    src/scene/Scene.cpp)
target_include_directories(fig_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(fig_core PRIVATE ${FIG_WARNINGS})

# view: рендер на OpenGL + GLFW и виджеты интерфейса.
add_library(fig_view
    src/render/Window.cpp
    src/render/OpenGLCanvas.cpp
    src/ui/ThemeButton.cpp
    src/ui/IconButton.cpp
    src/ui/Toolbar.cpp)
target_include_directories(fig_view PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(fig_view PUBLIC fig_core PRIVATE glfw OpenGL::GL)
target_compile_options(fig_view PRIVATE ${FIG_WARNINGS})

add_executable(figures src/app/main.cpp)
target_link_libraries(figures PRIVATE fig_view)
target_compile_options(figures PRIVATE ${FIG_WARNINGS})

include(CTest)
if(BUILD_TESTING)
    find_package(GTest QUIET)
    if(NOT GTest_FOUND)
        include(FetchContent)
        FetchContent_Declare(googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.14.0
            GIT_SHALLOW TRUE)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()
    add_executable(fig_tests tests/shape_tests.cpp)
    target_link_libraries(fig_tests PRIVATE fig_core GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(fig_tests)
endif()

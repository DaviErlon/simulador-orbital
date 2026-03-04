cmake_minimum_required(VERSION 3.10)

project(Simulador)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(app
    src/main.cpp
)

target_include_directories(app PRIVATE include)

add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/app
    DEPENDS app
)

target_link_libraries(app
    glfw
    OpenGL::GL
    OpenGL::GLU
)
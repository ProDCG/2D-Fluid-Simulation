cmake_minimum_required(VERSION 3.27)
project(2D_Fluid_Simulation)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(2D_Fluid_Simulation main.cpp
        solver.h
        renderer.h
)

target_link_libraries(2D_Fluid_Simulation sfml-graphics)

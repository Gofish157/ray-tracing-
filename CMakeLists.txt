cmake_minimum_required(VERSION 3.16)
project(ray_traice)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL3 REQUIRED CONFIG)

add_executable(ray_traice main.cpp)

target_link_libraries(ray_traice
        PRIVATE
        SDL3::SDL3
)
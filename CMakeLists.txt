cmake_minimum_required(VERSION 3.1)

project("Raycasting")

file(GLOB_RECURSE SRCS src/*)

add_executable(
        Raycasting
        ${SRCS}
)

target_link_libraries(Raycasting SDL2)
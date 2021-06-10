cmake_minimum_required(VERSION 3.20)

project(game)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(game ${SOURCES})

target_link_libraries(game SDL2main SDL2 SDL2_image jsoncpp)

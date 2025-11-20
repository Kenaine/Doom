cmake_minimum_required(VERSION 3.20)
project(Doom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(doom
    Doom/main.cpp
    Doom/Player.cpp
    Doom/RayCaster.cpp
)

target_include_directories(doom PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_directories(doom PRIVATE /usr/local/lib)
target_link_libraries(doom PRIVATE 
    sfml-graphics sfml-window sfml-system sfml-audio
)
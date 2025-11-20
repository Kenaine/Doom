cmake_minimum_required(VERSION 3.16)
project(doom)

set(CMAKE_CXX_STANDARD 17)

add_executable(doom
    Doom/main.cpp
    Doom/Player.cpp
    Doom/RayCaster.cpp
    Doom/Renderer3D.cpp
)

target_include_directories(doom PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(doom PRIVATE ${CMAKE_SOURCE_DIR}/lib)

# Link libraries manually
target_link_libraries(doom PRIVATE sfml-graphics sfml-window sfml-system)
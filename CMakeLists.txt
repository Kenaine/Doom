cmake_minimum_required(VERSION 3.16)
project(doom)

set(CMAKE_CXX_STANDARD 17)

# Use static SFML libraries
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(doom
    Doom/main.cpp
    Doom/Player.cpp
    Doom/RayCaster.cpp
    Doom/Renderer3D.cpp
)

target_include_directories(doom PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link SFML libraries
target_link_libraries(doom PRIVATE SFML::Graphics SFML::Window SFML::System)
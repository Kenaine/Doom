cmake_minimum_required(VERSION 3.16)
project(doom VERSION 1.0.0)

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

# Link SFML libraries statically to reduce dependencies
target_link_libraries(doom PRIVATE SFML::Graphics SFML::Window SFML::System)

# Set Windows subsystem for GUI application (removes console window)
if(WIN32)
    set_target_properties(doom PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Copy Assets to build directory
add_custom_command(TARGET doom POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:doom>/Assets
    COMMENT "Copying Assets to build directory"
)

# Installation rules
install(TARGETS doom DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Assets DESTINATION .)

# CPack configuration for creating distributable packages
set(CPACK_PACKAGE_NAME "Doom-Raycaster")
set(CPACK_PACKAGE_VENDOR "Kenaine")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "3D Raycasting Doom-style Game")
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)

if(WIN32)
    # Windows packaging
    set(CPACK_GENERATOR "ZIP")
else()
    # Linux packaging
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)
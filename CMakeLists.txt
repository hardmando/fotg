
cmake_minimum_required(VERSION 3.30)
project(fotg)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(fotg ${SOURCES})

# --- SDL2 + SDL2_image ---
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

# Include directories
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(fotg
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)


cmake_minimum_required(VERSION 3.30)
project(fotg)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(fotg ${SOURCES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h)
find_library(SDL2_IMAGE_LIBRARY SDL2_image)

include_directories(${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(fotg ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY})


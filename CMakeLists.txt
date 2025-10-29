cmake_minimum_required(VERSION 3.30)
project(fotg)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Sources + includes ---
include_directories(include)
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(fotg ${SOURCES})

# --- pkg-config for SDL2 ---
find_package(PkgConfig REQUIRED)
# On Apple we only want the cflags and include dirs from pkg-config.
# We'll handle the actual linking differently to avoid -lSDL2 being passed.
pkg_check_modules(SDL2_PKG REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE_PKG REQUIRED SDL2_image)

# include flags (works everywhere)
include_directories(
    ${SDL2_PKG_INCLUDE_DIRS}
    ${SDL2_IMAGE_PKG_INCLUDE_DIRS}
)
add_compile_options(${SDL2_PKG_CFLAGS_OTHER})   # preserves any other cflags

# --- Platform-specific linking ---
if(APPLE)
    # Detect Homebrew prefix (Apple Silicon vs Intel)
    if(EXISTS "/opt/homebrew/lib/libSDL2.dylib")
        set(HOMEBREW_PREFIX "/opt/homebrew")
    elseif(EXISTS "/usr/local/lib/libSDL2.dylib")
        set(HOMEBREW_PREFIX "/usr/local")
    else()
        message(FATAL_ERROR "SDL2 dylib not found in /opt/homebrew or /usr/local. Install via brew or adjust path.")
    endif()

    # Prevent pkg-config "libraries" string from injecting -lSDL2 into the final link line.
    # We'll use only the other flags (if any) and then explicitly add the dylibs.
    set(SDL2_LINK_FLAGS "${SDL2_PKG_LDFLAGS}")
    string(REPLACE "-lSDL2" "" SDL2_LINK_FLAGS "${SDL2_LINK_FLAGS}")
    string(REPLACE "-lSDL2_image" "" SDL2_LINK_FLAGS "${SDL2_LINK_FLAGS}")

    # If pkg-config supplied any -L or other flags, pass them via target_link_options (CMake >=3.13)
    if(SDL2_LINK_FLAGS)
        # Split into tokens and add as linker options
        separate_arguments(SDL2_LINK_FLAGS)
        target_link_options(fotg PRIVATE ${SDL2_LINK_FLAGS})
    endif()

    # Explicit dylib paths (guaranteed)
    target_link_libraries(fotg PRIVATE
        "${HOMEBREW_PREFIX}/lib/libSDL2.dylib"
        "${HOMEBREW_PREFIX}/lib/libSDL2_image.dylib"
    )

else()
    # On Linux/Arch: use pkg-config's libraries directly
    # SDL2_PKG_LIBRARIES contains the correct -L/-l flags for the platform
    target_link_libraries(fotg PRIVATE ${SDL2_PKG_LIBRARIES} ${SDL2_IMAGE_PKG_LIBRARIES})
endif()


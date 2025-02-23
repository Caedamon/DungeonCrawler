# Minimum required CMake version
cmake_minimum_required(VERSION 3.16)

# Project name and C++ standard
project(DungeonCrawler CXX)
set(CMAKE_CXX_STANDARD 20)

# Include FetchContent for dependency management
include(FetchContent)

# Function to add external dependencies via Git
function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

# Add Raylib dependency
set(RAYLIB_LIB raylib)
find_package(${RAYLIB_LIB} QUIET)

if (NOT ${RAYLIB_LIB}_FOUND)
    message(STATUS "Fetching Raylib from GitHub...")
    include_dependency(${RAYLIB_LIB} https://github.com/raysan5/raylib.git 5.5)
else()
    message(STATUS "Using local Raylib installation.")
endif()

# Include the header files directory
include_directories(include)

# Add executable and source files
add_executable(DungeonCrawler
        src/main.cpp
        src/dungeon.cpp
        src/player.cpp
        src/game.cpp
        include/dungeon.h
        include/player.h
        include/game.h
        src/ui.cpp
        include/ui.h
        src/button.cpp
        include/button.h
        src/skills.cpp
        include/skills.h
        src/equipment.cpp
        include/equipment.h
        src/monsters.cpp
        include/monsters.h
        include/game_state.h
)

# Include Raylib headers
target_include_directories(DungeonCrawler PRIVATE ${raylib_INCLUDE_DIRS})

# Link libraries (Raylib + Windows-specific libraries)
if (WIN32)
    target_link_libraries(DungeonCrawler PRIVATE ${RAYLIB_LIB} winmm)
elseif (APPLE)
    target_link_libraries(DungeonCrawler PRIVATE ${RAYLIB_LIB} "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
else()
    target_link_libraries(DungeonCrawler PRIVATE ${RAYLIB_LIB} m GL pthread dl X11)
endif()

# Ensure the resources folder is copied to the build directory
add_custom_command(TARGET DungeonCrawler POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources" "${CMAKE_BINARY_DIR}/resources"
)

cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(minesweeper)

set(SRC
    "src/main.cpp"
    "src/log.h"
    "src/tile.h"
    "src/tile.cpp"
    "src/game.cpp"
    "src/game.h"
    "src/utils.h"
    "src/utils.cpp"
    "src/renderable.h"
    "src/renderable.cpp"
    "src/clickable.cpp"
    "src/clickable.h"
    "src/listable.cpp"
    "src/listable.h"
    "src/assetloader.h"
    "src/assetloader.cpp"
)

add_executable(minesweeper ${SRC})

set_target_properties(minesweeper PROPERTIES
    CXX_STANDARD 17
)

if(EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind -s USE_SDL=2 -s USE_SDL_IMAGE=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file ../res --use-preload-plugins")

    # Set output file type to HTML
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
else()
    # Platform-specific handling (Linux/Windows) from your previous setup
    if(WIN32)
        if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
            set(ARCH "x64")
        else ()
            set(ARCH "x86")
        endif ()

        # SDL for Windows
        target_link_directories(minesweeper PRIVATE "vendor/SDL2/lib/${ARCH}")
        target_include_directories(minesweeper PRIVATE "vendor/SDL2/include")
        target_link_libraries(minesweeper PRIVATE SDL2 SDL2Main)

        add_custom_command(TARGET minesweeper POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2/lib/${ARCH}/SDL2.dll"
            "${CMAKE_BINARY_DIR}/bin/minesweeper-${CMAKE_BUILD_TYPE}/SDL2.dll")

    else()
        # Linux-specific handling
        find_package(SDL2 REQUIRED)
        include_directories(${SDL2_INCLUDE_DIRS})
        target_link_libraries(minesweeper PRIVATE ${SDL2_LIBRARIES})
    endif()
endif()

# spdlog
add_subdirectory("vendor/spdlog")
target_include_directories(minesweeper PRIVATE "vendor/spdlog/include")

# Post-build command for copying resources
add_custom_command(TARGET minesweeper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/res"
    "${CMAKE_BINARY_DIR}/res")

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(Minesweeper)

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

add_executable(Minesweeper ${SRC})

set_target_properties(Minesweeper PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Minesweeper-${CMAKE_BUILD_TYPE}"
    CXX_STANDARD 17
)

# Platform-specific configurations
if(WIN32)
    # Windows specific settings
    # Support both 32 and 64 bit builds
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(ARCH "x64")
    else ()
        set(ARCH "x86")
    endif ()

    # SDL2 for Windows
    target_link_directories(Minesweeper PRIVATE "vendor/SDL2/lib/${ARCH}")
    target_include_directories(Minesweeper PRIVATE "vendor/SDL2/include")
    target_link_libraries(Minesweeper PRIVATE SDL2 SDL2Main)

    add_custom_command(TARGET Minesweeper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2/lib/${ARCH}/SDL2.dll"
        "${CMAKE_BINARY_DIR}/bin/Minesweeper-${CMAKE_BUILD_TYPE}/SDL2.dll")

else()
    # Linux specific settings
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(Minesweeper PRIVATE ${SDL2_LIBRARIES})

endif()

# Common to both platforms
add_custom_command(TARGET Minesweeper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/res"
    "${CMAKE_BINARY_DIR}/bin/Minesweeper-${CMAKE_BUILD_TYPE}/res")

# spdlog
add_subdirectory("vendor/spdlog")
target_include_directories(Minesweeper PRIVATE "vendor/spdlog/include")

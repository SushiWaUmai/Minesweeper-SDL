cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(Minesweeper)

set(SRC "src/main.cpp")
add_executable(Minesweeper ${SRC})

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	set(ARCH "x64")
else ()
	set(ARCH "x86")
endif ()

message(${CMAKE_SYSTEM_PROCESSOR})

target_link_directories(Minesweeper PRIVATE "vendor/SDL2/lib/${ARCH}")
target_include_directories(Minesweeper PRIVATE "vendor/SDL2/include")
target_link_libraries(Minesweeper PRIVATE SDL2 SDL2Main)

set_target_properties(Minesweeper PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Minesweeper-${CMAKE_BUILD_TYPE}"
)

add_custom_command(TARGET Minesweeper POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2/lib/${ARCH}/SDL2.dll"
	"${CMAKE_BINARY_DIR}/bin/Minesweeper-${CMAKE_BUILD_TYPE}/SDL2.dll")

cmake_minimum_required(VERSION 3.30)
project(miniguys)

# Set some global configs
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIB_NAME lib_${PROJECT_NAME})
set(TEST_NAME test_${PROJECT_NAME})

set(RENDERER_DRIVER "sdl" CACHE STRING "Some user-specified option")

# Add vendor submodules
add_subdirectory(vendor/sdl)
add_subdirectory(vendor/sdl_image)
add_subdirectory(vendor/klib)

# Setup static files
file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/miniguys/shaders DESTINATION ${PROJECT_BINARY_DIR})

# Main library
set(${LIB_NAME}_sources
    miniguys/debug.c

    miniguys/renderer/player/player_renderer.c
    miniguys/renderer/sdl/sdl_renderer.c
    miniguys/renderer/sprite.c

    miniguys/event/event.c

    miniguys/input/input.c

    miniguys/math/vec2f.c

    miniguys/player/player.c

    miniguys/game/game.c
)

if(RENDERER_DRIVER STREQUAL "sdl")
    # SDL Renderer
    list(APPEND ${LIB_NAME}_sources miniguys/renderer/sdl/sdl_renderer.c)

    # SDL Time
    list(APPEND ${LIB_NAME}_sources miniguys/time/sdl/sdl_time.c)
endif()

# Print source fieles
message(STATUS "Sources: ${${LIB_NAME}_sources}")

add_library(
    ${LIB_NAME} STATIC
    ${${LIB_NAME}_sources}
)

target_compile_features(${LIB_NAME} PRIVATE c_std_17)
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${LIB_NAME} PUBLIC SDL3::SDL3 SDL3_image::SDL3_image lib_klib m)

# Executable
add_executable(
    ${PROJECT_NAME}

    miniguys/main.c
)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})

# Test executable
set(test_sources
    miniguys/test.c

    miniguys/renderer/sprite.test.c
)

if(RENDERER_DRIVER STREQUAL "sdl")
    list(APPEND test_sources miniguys/renderer/sdl/sdl_renderer.test.c)
endif()

add_executable(
    ${TEST_NAME}
    ${test_sources}
)

target_compile_features(${TEST_NAME} PRIVATE c_std_17)
target_link_libraries(${TEST_NAME} PRIVATE ${LIB_NAME})

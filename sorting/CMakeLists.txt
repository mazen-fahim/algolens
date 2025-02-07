# Minimum cmake required to compile this project
cmake_minimum_required(VERSION 3.10)

# Project information
project("algolens"
  VERSION 1.0
  DESCRIPTION "An algorithm visualizer"
  LANGUAGES C
)

# Generate compile_commands.json for clang LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(CREATE_LINK
  "${CMAKE_BINARY_DIR}/compile_commands.json"
  "${CMAKE_SOURCE_DIR}/compile_commands.json"
  SYMBOLIC
)

# Set the C standard used to compile this project
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

add_executable(algolens
  src/Draw.c
  src/GameLoop.c
  src/GameObjects.c
  src/GamePhysics.c
  src/HandleEvents.c
  src/Init.c
  src/LinkedLists.c
  src/SortingAlgo.c
  src/main.c
)

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
  # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
  target_link_libraries(algolens PRIVATE SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(algolens PRIVATE SDL2::SDL2)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
  target_link_libraries(algolens PUBLIC ${MATH_LIBRARY})
endif()

target_include_directories(algolens PRIVATE "include/")

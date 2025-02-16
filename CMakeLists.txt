cmake_minimum_required(VERSION 3.31)

project("algolens"
  VERSION 1.0
  DESCRIPTION "Algorithm Viusalizer"
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(CREATE_LINK
  "${CMAKE_BINARY_DIR}/compile_commands.json"
  "${CMAKE_SOURCE_DIR}/compile_commands.json"
  SYMBOLIC
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

# Add Executable
add_executable(algolens
  src/main.cpp
  src/GameObject.cpp
  src/Maze.cpp
  src/Cell.cpp
  src/EventHandler.cpp
  src/App.cpp
  src/UI.cpp
  src/Bar.cpp
  src/Sort.cpp
  external/imgui/imgui.cpp
  external/imgui/imgui_demo.cpp
  external/imgui/imgui_draw.cpp
  external/imgui/imgui_tables.cpp
  external/imgui/imgui_widgets.cpp
  external/imgui/backends/imgui_impl_sdl3.cpp
  external/imgui/backends/imgui_impl_sdlrenderer3.cpp
)

target_link_libraries(algolens PRIVATE SDL3::SDL3)


target_include_directories(algolens PRIVATE external/imgui external/imgui/backends)

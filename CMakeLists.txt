cmake_minimum_required(VERSION 3.15)
project(aio VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Cari SDL3
find_package(SDL3 CONFIG REQUIRED)

# Tambahkan direktori imgui
add_subdirectory(third_party/imgui)

# Kumpulkan semua source files
set(SOURCES
  src/main.cpp
  src/core/Application.cpp
  src/core/Window.cpp
  src/renderer/Renderer.cpp
  src/ui/UIManager.cpp
  src/features/FeatureManager.cpp
  src/features/ExampleFeature.cpp
)

# Tambahkan imgui source
set(IMGUI_SOURCES
  third_party/imgui/imgui.cpp
  third_party/imgui/imgui_demo.cpp
  third_party/imgui/imgui_draw.cpp
  third_party/imgui/imgui_tables.cpp
  third_party/imgui/imgui_widgets.cpp
  third_party/imgui/backends/imgui_impl_sdl3.cpp
  third_party/imgui/backends/imgui_impl_sdlrenderer3.cpp
)

# Buat executable
add_executable(aio ${SOURCES} ${IMGUI_SOURCES})

# Target include directories
target_include_directories(aio PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends
)

# Link SDL3
target_link_libraries(aio PRIVATE SDL3::SDL3)

# Set output directory
set_target_properties(aio PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

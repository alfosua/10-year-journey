cmake_minimum_required(VERSION 3.28)
project(ten_year_journey LANGUAGES CXX)

# Configure strict C++26 standard
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Clangd / IDE intellisense support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch dependencies
include(FetchContent)

# raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 6.0
  GIT_SHALLOW TRUE
)

# raylib-cpp
FetchContent_Declare(
  raylib_cpp
  GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
  GIT_TAG v6.0.3
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib raylib_cpp)

# Define executable and link libraries
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib raylib_cpp)

# macOS-specific dependencies for raylib
if(APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE
    "-framework IOKit"
    "-framework Cocoa"
    "-framework OpenGL"
  )
endif()

cmake_minimum_required(VERSION 3.10)
project(gl C CXX)

if (APPLE)
    # macos下使用clang编译
    set(CMAKE_C_COMPILER /Library/Developer/CommandLineTools/usr/bin/cc)
    set(CMAKE_CXX_COMPILER /Library/Developer/CommandLineTools/usr/bin/c++)
endif()

set(CMAKE_CXX_STANDARD 17)

# glm是头文件库，不需要单独编译
add_subdirectory(3rdparty/glad)
add_subdirectory(3rdparty/glfw)

file(GLOB SOURCES "src/*.cpp")
add_library(core STATIC ${SOURCES})
target_include_directories(core PUBLIC include 3rdparty/glad/include 3rdparty/glfw/include 3rdparty/glm)
target_link_libraries(core PUBLIC glad glfw)

add_executable(demo demo1.cpp)
target_link_libraries(demo PRIVATE core)

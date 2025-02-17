cmake_minimum_required(VERSION 3.4)
project(learnGL C CXX)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)

file(GLOB SOURCES "src/*.cpp")
add_library(core STATIC ${SOURCES})
target_include_directories(core PUBLIC include glad/include glfw/include glm/glm)
target_link_libraries(core PUBLIC glad glfw glm)

add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE core)

cmake_minimum_required(VERSION 3.6.0)
project(Win_Graphics_Test LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories("${PROJECT_SOURCE_DIR}/../../TCEngine/src")
add_subdirectory("${PROJECT_SOURCE_DIR}/../../TCEngine" "${PROJECT_SOURCE_DIR}/TCEngine")

add_executable (Win_Graphics_Test "Main.cpp" )

target_link_libraries (Win_Graphics_Test PRIVATE TCEngine)
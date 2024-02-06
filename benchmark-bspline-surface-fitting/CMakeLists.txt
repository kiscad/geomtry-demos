cmake_minimum_required(VERSION 3.10)
project(demo)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Catch2 3 REQUIRED)
find_package(VTK)
find_package(OpenCASCADE REQUIRED)

include_directories(${OpenCASCADE_INCLUDE_DIR})
message(${OpenCASCADE_INCLUDE_DIR})

add_executable(demo main.cpp)

target_link_libraries(demo ${OpenCASCADE_LIBRARIES} Catch2::Catch2WithMain)

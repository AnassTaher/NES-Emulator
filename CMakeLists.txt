cmake_minimum_required(VERSION 3.26)
project(nes)


set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
set(SDL2_PATH "C:/SDL2-2.28.2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${SDL2_INCLUDE_DIR}
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cc"
)

add_executable(nes ${all_SRCS} main.cc)

target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARY})

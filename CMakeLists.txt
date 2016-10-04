cmake_minimum_required(VERSION 3.6)
project(Fleur)

add_definitions(-std=c++11)

set(SOURCE_FILES main.cpp)
add_executable(fleur_run ${SOURCE_FILES})

include_directories(fleur_src)

add_subdirectory(fleur_src)
add_subdirectory(fleur_tests)

target_link_libraries(fleur_run fleur_src)
cmake_minimum_required(VERSION 3.6)
project(Fleur)

add_definitions(-std=c++11)

set(SOURCE_FILES main.cpp)
add_executable(fleur_run ${SOURCE_FILES})

### INCLUDE BOOST
find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()
add_executable(BoostTest main.cpp)
if(Boost_FOUND)
    target_link_libraries(BoostTest ${Boost_LIBRARIES})
endif()

include(cmake/PreventInSourceBuilds.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
find_package(Gumbo REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/gumbo-query/include)
include_directories(${Gumbo_INCLUDE_DIRS})
include_directories(${gumbo_query_SOURCE_DIRECTORY})
#
#file(GLOB LIBRARIES "${PROJECT_SOURCE_DIR}/gumbo-query/lib/libgq.dylib")
#message("LIBRARIES = ${LIBRARIES}")
add_subdirectory(${PROJECT_SOURCE_DIR}/gumbo-query/src)

include_directories(fleur_src/include)

add_subdirectory(fleur_src)
add_subdirectory(fleur_tests)

target_link_libraries(fleur_run fleur_src curl gumbo_query_shared)
cmake_minimum_required(VERSION 3.6)
project(Fleur)

add_definitions(-std=c++11)


if(NOT ${CMAKE_VERSION} LESS 3.2)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    message(STATUS "Checking compiler flags for C++11 support.")
    # Set C++11 support flags for various compilers
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
    check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
        message(STATUS "C++11 is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        endif()
    elseif(COMPILER_SUPPORTS_CXX0X)
        message(STATUS "C++0x is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        endif()
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endif()


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

##Gumbo parser
include(cmake/PreventInSourceBuilds.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
find_package(Gumbo REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/gumbo-query/include)
include_directories(${Gumbo_INCLUDE_DIRS} ${gumbo_query_SOURCE_DIRECTORY})
add_subdirectory(${PROJECT_SOURCE_DIR}/gumbo-query/src)

# https://whoshuu.github.io/cpr/introduction.html lib C++ Requests: Curl for People
add_subdirectory(opt)
include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})


## Fleur
include_directories(fleur_src/include )

add_subdirectory(fleur_src)
add_subdirectory(fleur_tests)

target_link_libraries(fleur_run fleur_src curl ${CPR_LIBRARIES} gumbo_query_shared)



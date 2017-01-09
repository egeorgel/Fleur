cmake_minimum_required(VERSION 2.8)
project(Fleur)
include(CTest)


#C++11 Support
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



### INCLUDE BOOST
find_package(Boost COMPONENTS system filesystem program_options regex REQUIRED)
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()


### CPR & JSON
set(JSON_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/submodules/json/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/json/)
if(WIN32)
    option(CMAKE_USE_OPENSSL "Use OpenSSL code. Experimental" OFF)
endif()
set(BUILD_CPR_TESTS OFF CACHE BOOL "Don't build cpr tests")
find_package(CURL)
if(CURL_FOUND)
    set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
endif()
add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/cpr/)
include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})


### Libtwitcurl
add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/twitcurl/libtwitcurl/)
include_directories(${PROJECT_SOURCE_DIR}/submodules/twitcurl/libtwitcurl/)


### GoogleTests
add_subdirectory(submodules/googletest)


### GUMBO QUERY
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/submodules/gumbo-query/lib/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/submodules/gumbo-query/cmake/)
find_package(Gumbo REQUIRED)
set(gumbo_query_SOURCE_DIRECTORY ${PROJECT_SOURCE_DIR}/submodules/gumbo-query/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/gumbo-query/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/gumbo-query/test)
include_directories(${PROJECT_SOURCE_DIR}/submodules/gumbo-query/include)
include_directories(${Gumbo_INCLUDE_DIRS} ${gumbo_query_SOURCE_DIRECTORY})



### FLEUR Static Lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/lib/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/lib/")
include_directories(fleur_core/include )
add_subdirectory(fleur_core/)
add_subdirectory(fleur_core_tests/)


#### Fleur CLI
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/bin/")
set(FLEUR_CLI_SOURCE_FILES fleur_cli/main.cpp)
add_executable(fleur_cli ${FLEUR_CLI_SOURCE_FILES})
target_link_libraries(fleur_cli ${Boost_LIBRARIES} fleur_static)


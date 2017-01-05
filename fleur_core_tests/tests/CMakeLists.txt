include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(fleur_core_tests
        parser/Requete_parser_test.cpp
        service/Http_test.cpp
        parser/Filter_test.cpp
        processing/Processing_http_test.cpp
        parser/Html_parser_test.cpp
        parser/Include_parser_test.cpp
        parser/Twitter_parser_test.cpp
        Libtwitcurl_test.cpp service/Twitter_test.cpp
        processing/Processing_twitter_test.cpp
        processing/processing_test.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
find_package(Gumbo REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/gumbo-query/include)

target_link_libraries(fleur_core_tests gtest gtest_main curl ${CPR_LIBRARIES} gumbo_query_shared libtwitcurl)
target_link_libraries(fleur_core_tests fleur_static_lib)
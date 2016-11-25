include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(fleurTest
        Requete_parser_test.cpp
        Http_test.cpp
        Filter_test.cpp
        Processing_test.cpp Html_parser_test.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
find_package(Gumbo REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/gumbo-query/include)


target_link_libraries(fleurTest gtest gtest_main curl ${CPR_LIBRARIES} gumbo_query_shared)
target_link_libraries(fleurTest fleur_src)

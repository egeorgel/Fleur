include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(fleurTest
        Requete_parser_test.cpp
        Http_test.cpp)

target_link_libraries(fleurTest gtest gtest_main curl)
target_link_libraries(fleurTest fleur_src)

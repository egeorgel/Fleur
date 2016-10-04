include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runFleurTests
        ParserTest.cpp)

target_link_libraries(runFleurTests gtest gtest_main)
target_link_libraries(runFleurTests fleur_src)

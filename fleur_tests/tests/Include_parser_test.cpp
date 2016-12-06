//
// Created by Edgar on 06/12/2016.
//


#include <gtest/gtest.h>
#include "Include_parser.h"

class Include_parser_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Include_parser_test() {}
};

TEST_F(Include_parser_test, parse_url_ALL_and_url) {
    const std::string input = "use twitter;";
    parser::Include include;
    EXPECT_TRUE(parser::doParse(input, include));
    ASSERT_EQ(include._module, "twitter");
}

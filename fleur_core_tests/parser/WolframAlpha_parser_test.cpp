//
// Created by Edgar on 26/12/2016.
//

#include <gtest/gtest.h>
#include <service/WolframAlpha.h>
#include "parser/Include_parser.h"

class WolframAlpha_parser_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~WolframAlpha_parser_test() {}
};


TEST_F(WolframAlpha_parser_test, parse_general_question) {
    std::string input = "EVALUATE x + 2 = 10;";
    fleur::parser::WolframAlpha wolframReq;
    EXPECT_TRUE(fleur::parser::doParse(input, wolframReq));
    ASSERT_EQ(wolframReq._action, "EVALUATE");
    ASSERT_EQ(wolframReq._to_evaluate, "x + 2 = 10");
}

TEST_F(WolframAlpha_parser_test, parse_app_id) {
    std::string input = "denis;";
    fleur::parser::WolframAlphaAppID wolframAppIDReq;
    EXPECT_TRUE(fleur::parser::doParse(input, wolframAppIDReq));
    ASSERT_EQ(wolframAppIDReq._appID, "denis");
}
//
// Created by Edgar on 26/12/2016.
//

#include <gtest/gtest.h>
#include <service/Twitter.h>
#include "parser/Include_parser.h"

class Twitter_parser_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Twitter_parser_test() {}
};


TEST_F(Twitter_parser_test, parse_url_ALL_and_url) {
    std::string input = "get tweets from twitter;";
    parser::Twitter twitterReq;
    EXPECT_TRUE(parser::doParse(input, twitterReq));
    ASSERT_EQ(twitterReq._crud, "get");
    ASSERT_EQ(twitterReq._actionName, "tweets");
    ASSERT_EQ(twitterReq._fromName, "twitter");

    input = "get tweets from . limit 2;";
    parser::Twitter twitterReq2;
    EXPECT_TRUE(parser::doParse(input, twitterReq2));
    ASSERT_EQ(twitterReq2._crud, "get");
    ASSERT_EQ(twitterReq2._actionName, "tweets");
    ASSERT_EQ(twitterReq2._fromName, ".");
    ASSERT_EQ(twitterReq2._limitName, "2");
}

TEST_F(Twitter_parser_test, parse_url_HTML_and_url) {
    std::string input = "get * from .;";
    parser::Twitter twitterReq;
    EXPECT_TRUE(parser::doParse(input, twitterReq));
    ASSERT_EQ(twitterReq._crud, "get");
    ASSERT_EQ(twitterReq._actionName, "*");
    ASSERT_EQ(twitterReq._fromName, ".");

    input = "get * from . limit 2;";
    parser::Twitter twitterReq2;
    EXPECT_TRUE(parser::doParse(input, twitterReq2));
    ASSERT_EQ(twitterReq2._crud, "get");
    ASSERT_EQ(twitterReq2._actionName, "*");
    ASSERT_EQ(twitterReq2._fromName, ".");
    ASSERT_EQ(twitterReq2._limitName, "2");
}


TEST_F(Twitter_parser_test, parse_url_HTML_select_h1_and_url) {
    std::string input = "get * from ProductHunt;";
    parser::Twitter twitterReq;
    EXPECT_TRUE(parser::doParse(input, twitterReq));
    ASSERT_EQ(twitterReq._crud, "get");
    ASSERT_EQ(twitterReq._actionName, "*");
    ASSERT_EQ(twitterReq._fromName, "ProductHunt");

    input = "get tweets from ProductHunt limit 2;";
    parser::Twitter twitterReq2;
    EXPECT_TRUE(parser::doParse(input, twitterReq2));
    ASSERT_EQ(twitterReq2._crud, "get");
    ASSERT_EQ(twitterReq2._actionName, "tweets");
    ASSERT_EQ(twitterReq2._fromName, "ProductHunt");
    ASSERT_EQ(twitterReq2._limitName, "2");
}

TEST_F(Twitter_parser_test, parse_url_HTML_select_h1_) {
    std::string input = "search \"text\" from *;";
    parser::Twitter twitterReq;
    EXPECT_TRUE(parser::doParse(input, twitterReq));
    ASSERT_EQ(twitterReq._crud, "search");
    ASSERT_EQ(twitterReq._actionName, "\"text\"");
    ASSERT_EQ(twitterReq._fromName, "*");

    input = "search \"text\" from * limit 2;";
    parser::Twitter twitterReq2;
    EXPECT_TRUE(parser::doParse(input, twitterReq2));
    ASSERT_EQ(twitterReq2._crud, "search");
    ASSERT_EQ(twitterReq2._actionName, "\"text\"");
    ASSERT_EQ(twitterReq2._fromName, "*");
    ASSERT_EQ(twitterReq2._limitName, "2");
}

TEST_F(Twitter_parser_test, parse_url_) {
    std::string input = "search \"text\" from twitter;";
    parser::Twitter twitterReq;
    EXPECT_TRUE(parser::doParse(input, twitterReq));
    ASSERT_EQ(twitterReq._crud, "search");
    ASSERT_EQ(twitterReq._actionName, "\"text\"");
    ASSERT_EQ(twitterReq._fromName, "twitter");

    input = "search \"text\" from twitter limit 2;";
    parser::Twitter twitterReq2;
    EXPECT_TRUE(parser::doParse(input, twitterReq2));
    ASSERT_EQ(twitterReq2._crud, "search");
    ASSERT_EQ(twitterReq2._actionName, "\"text\"");
    ASSERT_EQ(twitterReq2._fromName, "twitter");
    ASSERT_EQ(twitterReq2._limitName, "2");
}

TEST_F(Twitter_parser_test, parse_url_parse_url_) {
    std::string input = "get mentions from twitter;";
    parser::Twitter twitterReq;
    EXPECT_TRUE(parser::doParse(input, twitterReq));
    ASSERT_EQ(twitterReq._crud, "get");
    ASSERT_EQ(twitterReq._actionName, "mentions");
    ASSERT_EQ(twitterReq._fromName, "twitter");

    input = "get mentions from .;";
    parser::Twitter twitterReq2;
    EXPECT_TRUE(parser::doParse(input, twitterReq2));
    ASSERT_EQ(twitterReq2._crud, "get");
    ASSERT_EQ(twitterReq2._actionName, "mentions");
    ASSERT_EQ(twitterReq2._fromName, ".");

}

TEST_F(Twitter_parser_test, parrl_parse_rl_) {
    std::string input = "get mentions from twitter limit 2;";
    parser::Twitter twitterReq;
    EXPECT_TRUE(parser::doParse(input, twitterReq));
    ASSERT_EQ(twitterReq._crud, "get");
    ASSERT_EQ(twitterReq._actionName, "mentions");
    ASSERT_EQ(twitterReq._fromName, "twitter");
    ASSERT_EQ(twitterReq._limitName, "2");

    input = "get mentions from . limit 2;";
    parser::Twitter twitterReq2;
    EXPECT_TRUE(parser::doParse(input, twitterReq2));
    ASSERT_EQ(twitterReq2._crud, "get");
    ASSERT_EQ(twitterReq2._actionName, "mentions");
    ASSERT_EQ(twitterReq2._fromName, ".");
    ASSERT_EQ(twitterReq2._limitName, "2");
}

TEST_F(Twitter_parser_test, parse_url_parse_u_) {
    std::string input = "post \"new tweet\";";
    parser::Twitter twitterReq;
    EXPECT_TRUE(parser::doParse(input, twitterReq));
    ASSERT_EQ(twitterReq._crud, "post");
    ASSERT_EQ(twitterReq._actionName, "\"new tweet\"");
}

TEST_F(Twitter_parser_test, parse_ur) {
    std::string input = "delete 934839843522;";
    parser::Twitter twitterReq;
    EXPECT_TRUE(parser::doParse(input, twitterReq));
    ASSERT_EQ(twitterReq._crud, "delete");
    ASSERT_EQ(twitterReq._actionName, "934839843522");
}

TEST_F(Twitter_parser_test, rse_url_parse_u_) {
    std::string input = "get trends;";
    parser::Twitter twitterReq;
    EXPECT_TRUE(parser::doParse(input, twitterReq));
    ASSERT_EQ(twitterReq._crud, "get");
    ASSERT_EQ(twitterReq._actionName, "trends");

}
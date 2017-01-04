//
// Created by Edgar on 03/01/2017.
//

#include <gtest/gtest.h>
#include <parser/Wiki_parser.h>


class Wiki_parser_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Wiki_parser_test() {}
};

TEST_F(Wiki_parser_test, findMostRelativeSubjectWithLimit) {
    const std::string input = "search Java from wiki limit 4;";
    parser::Wiki wiki;
    EXPECT_TRUE(parser::doParse(input, wiki));
    ASSERT_EQ(wiki._crud, "search");
    ASSERT_EQ(wiki._articleName, "Java");
    ASSERT_EQ(wiki._fromName, "wiki");
    ASSERT_EQ(wiki._limit, "4");

    const std::string input2 = "search Java from wiki;";
    parser::Wiki wiki2;
    EXPECT_TRUE(parser::doParse(input2, wiki2));
    ASSERT_EQ(wiki2._crud, "search");
    ASSERT_EQ(wiki._articleName, "Java");
    ASSERT_EQ(wiki2._fromName, "wiki");
}

TEST_F(Wiki_parser_test, getArticleHeader) {
    const std::string input = "get (header) java from wiki;";
    parser::Wiki wiki;
    EXPECT_TRUE(parser::doParse(input, wiki));
    ASSERT_EQ(wiki._crud, "get");
    ASSERT_EQ(wiki._format, "header");
    ASSERT_EQ(wiki._articleName, "java");
    ASSERT_EQ(wiki._fromName, "wiki");
}

TEST_F(Wiki_parser_test, getArticleHtml) {
    const std::string input = "get (html) java from wiki;";
    parser::Wiki wiki;
    EXPECT_TRUE(parser::doParse(input, wiki));
    ASSERT_EQ(wiki._crud, "get");
    ASSERT_EQ(wiki._format, "html");
    ASSERT_EQ(wiki._articleName, "java");
    ASSERT_EQ(wiki._fromName, "wiki");

    const std::string input2 = "get java from wiki;";
    parser::Wiki wiki2;
    EXPECT_TRUE(parser::doParse(input2, wiki2));
    ASSERT_EQ(wiki2._crud, "get");
    ASSERT_EQ(wiki2._format, "");
    ASSERT_EQ(wiki2._articleName, "java");
    ASSERT_EQ(wiki2._fromName, "wiki");
}

TEST_F(Wiki_parser_test, getArticleText) {
    const std::string input = "get (txt) java from wiki;";
    parser::Wiki wiki;
    EXPECT_TRUE(parser::doParse(input, wiki));
    ASSERT_EQ(wiki._crud, "get");
    ASSERT_EQ(wiki._format, "txt");
    ASSERT_EQ(wiki._articleName, "java");
    ASSERT_EQ(wiki._fromName, "wiki");
}
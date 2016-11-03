//
// Created by Edgar on 16/10/2016.
//

#include <string>
#include <gtest/gtest.h>
#include <vector>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <Requete_parser.h>

class Requete_parser_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Requete_parser_test() {}
};

TEST_F(Requete_parser_test, splitParametersStr) {
    parser::Requete requete;
    requete._parametersStr = "name=denis, age=12, date=12/12/12";
    parser::type_parameterS output;
    output.push_back(std::make_pair("name", "denis"));
    output.push_back(std::make_pair("age", "12"));
    output.push_back(std::make_pair("date", "12/12/12"));
    requete.splitParametersStr();
    ASSERT_EQ(requete._parameters, output);
}


TEST_F(Requete_parser_test, parse_url_ALL_and_url) {
    const std::string input = "select * from \"http://denis.fr\";";
    parser::Requete requete;
    EXPECT_TRUE(parser::doParse(input, requete));
    ASSERT_EQ(requete._url, "http://denis.fr");
    ASSERT_EQ(requete._format, "*");
}

TEST_F(Requete_parser_test, parse_url_HTML_and_url) {
    const std::string input = "select html from \"http://denis.fr\";";
    parser::Requete requete;
    EXPECT_TRUE(parser::doParse(input, requete));
    ASSERT_EQ(requete._url, "http://denis.fr");
    ASSERT_EQ(requete._format, "html");
}

TEST_F(Requete_parser_test, parse_url_XML_and_url) {
    const std::string input = "select xml from \"http://denis.fr\";";
    parser::Requete requete;
    EXPECT_TRUE(parser::doParse(input, requete));
    ASSERT_EQ(requete._url, "http://denis.fr");
    ASSERT_EQ(requete._format, "xml");
}

TEST_F(Requete_parser_test, parse_url_JSON_and_url) {
    const std::string input = "select json from \"http://denis.fr\";";
    parser::Requete requete;
    EXPECT_TRUE(parser::doParse(input, requete));
    ASSERT_EQ(requete._url, "http://denis.fr");
    ASSERT_EQ(requete._format, "json");
}

TEST_F(Requete_parser_test, parse_url_JSON_and_url_and_get_1p) {
    const std::string input = "select json from \"http://denis.fr\" get (name=denis);";
    parser::Requete requete;
    EXPECT_TRUE(parser::doParse(input, requete));
    ASSERT_EQ(requete._url, "http://denis.fr");
    ASSERT_EQ(requete._format, "json");
    ASSERT_EQ(requete._crud, "get");
    ASSERT_EQ(requete._parametersStr, "name=denis");

    parser::type_parameterS output;
    output.push_back(std::make_pair("name", "denis"));

    ASSERT_EQ(requete._parameters, output);
}

TEST_F(Requete_parser_test, parse_url_JSON_and_url_and_post_3p) {
    const std::string input = "select json from \"http://denis.fr\" post (name=denis, age=12, date=12/12/12);";
    parser::Requete requete;
    EXPECT_TRUE(parser::doParse(input, requete));
    ASSERT_EQ(requete._url, "http://denis.fr");
    ASSERT_EQ(requete._format, "json");
    ASSERT_EQ(requete._crud, "post");
    ASSERT_EQ(requete._parametersStr, "name=denis,age=12,date=12/12/12");

    parser::type_parameterS output;
    output.push_back(std::make_pair("name", "denis"));
    output.push_back(std::make_pair("age", "12"));
    output.push_back(std::make_pair("date", "12/12/12"));

    ASSERT_EQ(requete._parameters, output);
}
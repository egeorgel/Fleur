//
// Created by Edgar on 16/10/2016.
//

#include <string>
#include <gtest/gtest.h>
#include "Requete_parser.h"

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
    requete.splitParametersStr(requete._parametersStr, requete._parameters);
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


TEST_F(Requete_parser_test, parse_url_HTML_select_h1_and_url) {
    const std::string input = "select html (h1) from \"http://denis.fr\";";
    parser::Requete requete;
    EXPECT_TRUE(parser::doParse(input, requete));
    ASSERT_EQ(requete._url, "http://denis.fr");
    ASSERT_EQ(requete._format, "html");
    ASSERT_EQ(requete._selector, "h1");
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

TEST_F(Requete_parser_test, parse_url_JSON_and_url_and_get_3p_header_2p) {
    const std::string input = "select json "
                                "from \"http://denis.fr\" "
                                "get (name=denis, age=12, date=12/12/12) "
                                "header (tokenID=E223DEF, time=4);";
    parser::Requete requete;
    EXPECT_TRUE(parser::doParse(input, requete));
    ASSERT_EQ(requete._url, "http://denis.fr");
    ASSERT_EQ(requete._format, "json");
    ASSERT_EQ(requete._crud, "get");
    ASSERT_EQ(requete._parametersStr, "name=denis,age=12,date=12/12/12");
    ASSERT_EQ(requete._headersStr, "tokenID=E223DEF,time=4");

    parser::type_parameterS outputP;
    outputP.push_back(std::make_pair("name", "denis"));
    outputP.push_back(std::make_pair("age", "12"));
    outputP.push_back(std::make_pair("date", "12/12/12"));
    ASSERT_EQ(requete._parameters, outputP);

    parser::type_parameterS outputH;
    outputH.push_back(std::make_pair("tokenID", "E223DEF"));
    outputH.push_back(std::make_pair("time", "4"));
    ASSERT_EQ(requete._headers, outputH);
}

TEST_F(Requete_parser_test, parse_url_HTML_select_P_and_url_and_get_3p_header_2p) {
    const std::string input = "select html (p) "
            "from \"http://denis.fr\" "
            "get (name=denis, age=12, date=12/12/12) "
            "header (tokenID=E223DEF, time=4);";
    parser::Requete requete;
    EXPECT_TRUE(parser::doParse(input, requete));
    ASSERT_EQ(requete._url, "http://denis.fr");
    ASSERT_EQ(requete._format, "html");
    ASSERT_EQ(requete._selector, "p");
    ASSERT_EQ(requete._crud, "get");
    ASSERT_EQ(requete._parametersStr, "name=denis,age=12,date=12/12/12");
    ASSERT_EQ(requete._headersStr, "tokenID=E223DEF,time=4");

    parser::type_parameterS outputP;
    outputP.push_back(std::make_pair("name", "denis"));
    outputP.push_back(std::make_pair("age", "12"));
    outputP.push_back(std::make_pair("date", "12/12/12"));
    ASSERT_EQ(requete._parameters, outputP);

    parser::type_parameterS outputH;
    outputH.push_back(std::make_pair("tokenID", "E223DEF"));
    outputH.push_back(std::make_pair("time", "4"));
    ASSERT_EQ(requete._headers, outputH);
}
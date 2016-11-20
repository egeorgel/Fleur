//
// Created by Edgar on 06/11/2016.
//
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <gtest/gtest.h>
#include <Requete_parser.h>
#include <Http.h>
#include <HttpException.h>

class Http_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Http_test(){}
};

TEST_F(Http_test, http_showld_throw_exception) {
    parser::Requete req;

    try {
        Http http(req);
        FAIL();
    } catch (const HttpException &e) {
        ASSERT_STREQ("Requete must have an url", e.what());
    }

    req._url = "";
    try {
        Http http(req);
        FAIL();
    } catch (const HttpException &e) {
        ASSERT_STREQ("Requete must have an url", e.what());
    }
}

TEST_F(Http_test, http_init) {
    parser::Requete req;
    req._url = "http://denis.fr";

    Http http(req);
    ASSERT_EQ("http://denis.fr", http.get_requete()._url);
}

TEST_F(Http_test, http_downloadContent) {
    parser::Requete req;
    req._url = "https://raw.githubusercontent.com/AurelienGuerard/BigDataWithHadoop/master/README.md";

    Http http(req);
    ASSERT_EQ("# BigDataWithHadoop\n\nTP MapReduce.\nMap(), ShuffleAndSort(), Reduce() are implemented. Each step is displayed on the page.\n",
              http.downloadContent());
}

TEST_F(Http_test, http_downloadContent_showld_throw_exception) {
    parser::Requete req;
    req._url = "http://";

    try {
        Http http(req);
        http.downloadContent();
        FAIL();
    } catch (const HttpException &e) {
        ASSERT_STREQ("curl_easy_perform() failed: Couldn't resolve host name", e.what());
    }
}

TEST_F(Http_test, http_downloadJson) {
    parser::Requete req;
    req._url = "https://www.hutworks.net//test.php?json=ezd";
    req._format = "json";

    Http http(req);
    ASSERT_EQ("{\"test\":\"une chevre\",\"chat\":{\"fouine\":\"Fleur\"}}\n",
              http.downloadJson());
}

TEST_F(Http_test, http_post) {
    parser::Requete req;
    req._url = "http://httpbin.org/post";
    req._crud = "post";
    parser::type_parameterS param;
    param.push_back(std::make_pair("name", "denis"));
    param.push_back(std::make_pair("age", "12"));
    req._parameters = param;

    Http http(req);
    //parsing json
    std::stringstream ss;
    ss << http.post();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);

    ASSERT_EQ("12", pt.get<std::string>("form.age"));
    ASSERT_EQ("denis", pt.get<std::string>("form.name"));
}

TEST_F(Http_test, http_get) {
    parser::Requete req;
    req._url = "http://httpbin.org/get";
    req._crud = "get";
    parser::type_parameterS param;
    param.push_back(std::make_pair("name", "denis"));
    param.push_back(std::make_pair("age", "12"));
    req._parameters = param;

    Http http(req);

    std::stringstream ss;
    ss << http.get();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);
    //parsing json
    ASSERT_EQ("12", pt.get<std::string>("args.age"));
    ASSERT_EQ("denis", pt.get<std::string>("args.name"));
}
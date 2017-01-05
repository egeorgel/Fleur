//
// Created by Edgar on 06/11/2016.
//
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <gtest/gtest.h>
#include <parser/Requete_parser.h>
#include <service/Http.h>
#include <HttpException.h>
#include <json.hpp>

class Http_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Http_test(){}
};

TEST_F(Http_test, http_init) {
    fleur::parser::Requete req;
    req._url = "http://denis.fr";

    fleur::Http http(req);
    ASSERT_EQ("http://denis.fr", http.get_requete()._url);
}

TEST_F(Http_test, http_downloadContent) {
    fleur::parser::Requete req;
    req._url = "https://raw.githubusercontent.com/AurelienGuerard/BigDataWithHadoop/master/README.md";

    fleur::Http http(req);
    ASSERT_EQ("# BigDataWithHadoop\n\nTP MapReduce.\nMap(), ShuffleAndSort(), Reduce() are implemented. Each step is displayed on the page.",
              http.downloadContent());
}


TEST_F(Http_test, http_downloadJson) {
    fleur::parser::Requete req;
    req._url = "https://www.hutworks.net//test.php?json=ezd";
    req._format = "json";

    fleur::Http http(req);
    ASSERT_EQ("{\"test\":\"une chevre\",\"chat\":{\"fouine\":\"Fleur\"}}",
              http.downloadContent());
}

TEST_F(Http_test, http_post) {
    fleur::parser::Requete req;
    req._url = "http://httpbin.org/post";
    req._crud = "post";
    fleur::parser::type_parameterS param;
    param.push_back(std::make_pair("name", "denis"));
    param.push_back(std::make_pair("age", "12"));
    req._parameters = param;

    fleur::Http http(req);

    std::string returnPost = http.post();
    auto json = nlohmann::json::parse(returnPost);

    ASSERT_EQ("12", json["form"]["age"].get<std::string>());
    ASSERT_EQ("denis", json["form"]["name"].get<std::string>());
}

TEST_F(Http_test, http_get) {
    fleur::parser::Requete req;
    req._url = "http://httpbin.org/get";
    req._crud = "get";
    fleur::parser::type_parameterS param;
    param.push_back(std::make_pair("name", "denis"));
    param.push_back(std::make_pair("age", "12"));
    req._parameters = param;

    fleur::Http http(req);

    std::stringstream ss;
    ss << http.get();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);
    //parsing json
    ASSERT_EQ("12", pt.get<std::string>("args.age"));
    ASSERT_EQ("denis", pt.get<std::string>("args.name"));
}
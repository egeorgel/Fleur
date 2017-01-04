//
// Created by Edgar on 03/01/2017.
//

#include <cpr/parameters.h>
#include <cpr/cprtypes.h>
#include <cpr/api.h>
#include <boost/property_tree/json_parser.hpp>
#include <json.hpp>
#include "service/Wiki.h"


////https://en.wikipedia.org/w/api.php?action=opensearch&search=bee&limit=1&format=json
//std::string url("https://en.wikipedia.org/w/api.php?action=opensearch&format=json&search=Java&limit=3");
//std::string url1("http://en.wikipedia.org/w/api.php?action=query&prop=extracts&format=json&exintro=&titles=Stack%20Overflow");
//std::string url2("https://en.wikipedia.org/w/api.php?action=parse&page=java");

Wiki::type_listArticle Wiki::findMostRelativeSubjectWithLimit() const {
    assert(_wiki._crud == "search");
    assert(_wiki._fromName == "wikipedia");

    std::string limit = (_wiki._limit == "")? "10" : _wiki._limit;
    auto parameters = cpr::Parameters{{"action", "opensearch"},
                                      {"format", "json"},
                                      {"search", _wiki._articleName},
                                      {"limit", limit}};
    auto result = cpr::Get(cpr::Url{_urlApi}, parameters);

    return populatListArctivle(limit, result);
}


Wiki::type_article Wiki::getArticleHeader() const {
    assert(_wiki._crud == "get");
    assert(_wiki._fromName == "wikipedia");
    assert(_wiki._format == "header");

    auto parameters = cpr::Parameters{{"action", "query"},
                                      {"prop", "extracts"},
                                      {"format", "json"},
                                      {"exintro", ""},
                                      {"redirects", "1"},
                                      {"titles", _wiki._articleName}};
    auto result = cpr::Get(cpr::Url{_urlApi}, parameters);

    return populatArctivleHeader(result);
}

Wiki::type_article Wiki::getArticleHtml() const {
    assert(_wiki._crud == "get");
    assert(_wiki._fromName == "wikipedia");
    assert(_wiki._format == "html");

    auto parameters = cpr::Parameters{{"action", "opensearch"},
                                      {"format", "json"},
                                      {"search", _wiki._articleName},
                                      {"limit", "1"}};
    auto result = cpr::Get(cpr::Url{_urlApi}, parameters);

    Wiki::type_article ArticleNameAndUrl = getUrlArticle(result);

    auto resultHtml = cpr::Get(cpr::Url{ArticleNameAndUrl.second});
    ArticleNameAndUrl.second = resultHtml.text;
    return ArticleNameAndUrl;
}

Wiki::type_article Wiki::getArticleText() const {
    assert(_wiki._crud == "get");
    assert(_wiki._fromName == "wikipedia");
    assert(_wiki._format == "txt");

    auto parameters = cpr::Parameters{{"action", "opensearch"},
                                      {"format", "json"},
                                      {"search", _wiki._articleName}};
    auto result = cpr::Get(cpr::Url{_urlApi}, parameters);

    Wiki::type_article ArticleNameAndUrl = getUrlArticle(result);

    auto resultHtml = cpr::Get(cpr::Url{ArticleNameAndUrl.second});
    ArticleNameAndUrl.second = resultHtml.text;

    CDocument doc;
    doc.parse(resultHtml.text.c_str());
    CSelection c = doc.find("body");

    ArticleNameAndUrl.second = c.nodeAt(0).text();

    return ArticleNameAndUrl;
}

Wiki::type_listArticle Wiki::populatListArctivle(const std::string &limit, const cpr::Response &result) const {
    std::stringstream ss;
    ss << result.text;
    boost::property_tree::ptree pt;
    boost::property_tree::json_parser::read_json(ss, pt);

    type_listArticle listArticle;

    auto jsonP = nlohmann::json::parse(result.text);
    try {
        int index = 0;
        for(boost::property_tree::ptree::value_type &v : pt ){

            if (index == 1){
                int i = 0, intLimit = stoi(limit);
                for (boost::property_tree::ptree::value_type &vf : v.second) {
                    std::string key = vf.second.get<std::string>("");
                    listArticle.push_back(make_pair(key, std::string("")));
                    if (i == intLimit)
                        break;
                    ++i;
                }
            }

            if (index == 2){
                int i = 0, intLimit = stoi(limit);
                for (boost::property_tree::ptree::value_type &vf : v.second) {
                    listArticle[i].second = vf.second.get<std::string>("");
                    if (i == intLimit)
                        break;
                    ++i;
                }
                break;
            }

            ++index;
        }
    } catch (std::exception) {
        std::string key = "ERROR find most relative subject";
        listArticle.push_back(make_pair(key, jsonP.dump()));
    }
    return listArticle;
}

Wiki::type_article Wiki::populatArctivleHeader(const cpr::Response &result) const {
    std::__1::stringstream ss;
    ss << result.text;
    boost::property_tree::ptree pt;
    boost::property_tree::json_parser::read_json(ss, pt);

    type_article article(make_pair(std::string(""), std::string("")));

    auto jsonP = nlohmann::json::parse(result.text);
    try {
        article.first = jsonP["query"]["pages"]["72038"]["title"].get<std::string>();
        article.second = jsonP["query"]["pages"]["72038"]["extract"].get<std::string>();
    } catch (std::exception) {
        article.first = "ERROR get article";
        article.second = jsonP.dump();
    }
    return article;
}

Wiki::type_article Wiki::getUrlArticle(const cpr::Response &result) const {
    std::stringstream ss;
    ss << result.text;
    boost::property_tree::ptree pt;
    boost::property_tree::json_parser::read_json(ss, pt);

    Wiki::type_article articleWithUrl(make_pair(std::string(""), std::string("")));

    auto jsonP = nlohmann::json::parse(result.text);
    try {
        int index = 0;
        for(boost::property_tree::ptree::value_type &v : pt ){

            if (index == 1){
                for (boost::property_tree::ptree::value_type &vf : v.second) {
                    articleWithUrl.first = vf.second.get<std::string>("");
                    break;
                }
            }

            if (index == 3){
                for (boost::property_tree::ptree::value_type &vf : v.second) {
                    articleWithUrl.second = vf.second.get<std::string>("");
                    break;
                }
                break;
            }
            ++index;
        }
    } catch (std::exception) {
        articleWithUrl.first = "ERROR no article";
        articleWithUrl.second = jsonP.dump();
    }
    return articleWithUrl;
}
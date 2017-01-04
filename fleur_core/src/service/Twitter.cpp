//
// Created by Edgar on 27/12/2016.
//

#include <boost/property_tree/json_parser.hpp>
#include <json.hpp>
#include "service/Twitter.h"

/////////////////////
///     PUBLIC   ////
/////////////////////

Twitter::type_listOfTweet Twitter::getTimeLineFromUserWithLimit() {
    assert(_twitter._crud == "get");
    if ( !isLogIn() ) {
        Twitter::type_listOfTweet listOfTweet;
        listOfTweet.push_back(std::make_pair(std::string("ERROR"), std::string("Bad Authentication data")));
        return listOfTweet;
    }

    int limit = 200;
    if (_twitter._limitName != "")
        limit =  std::stoi( _twitter._limitName );

    bool isWorking;
    if (_twitter._fromName == "." || _twitter._fromName == "twitter") {
        isWorking = _twitCurl.timelineUserGet(true, true, limit);
    } else if (_twitter._fromName == "mentions"){
        return getTwitSelfMentioningWithLimit();
    }else {
        isWorking = _twitCurl.timelineUserGet(true, true, limit, _twitter._fromName);
    }
    std::string response = getWebResponse(isWorking);

    return json2TypeListOfTweetGetTimeLine(response);
}

Twitter::type_listOfTweet Twitter::searchForTwitContainStringWithLimit() {
    assert(_twitter._crud == "search");
    if ( !isLogIn() ) {
        Twitter::type_listOfTweet listOfTweet;
        listOfTweet.push_back(std::make_pair(std::string("ERROR"), std::string("Bad Authentication data")));
        return listOfTweet;
    }

    std::string limit("200");
    if (_twitter._limitName != "")
        limit =  _twitter._limitName;

    bool isWorking = _twitCurl.search(_twitter._actionName, limit);
    std::string response = getWebResponse(isWorking);

    return json2TypeListOfTweetSearch(response);
}

Twitter::type_listOfTweet Twitter::getTwitSelfMentioningWithLimit() {
    assert(_twitter._crud == "get");
    assert(_twitter._actionName == "mentions");
    if ( !isLogIn() ) {
        Twitter::type_listOfTweet listOfTweet;
        listOfTweet.push_back(std::make_pair(std::string("ERROR"), std::string("Bad Authentication data")));
        return listOfTweet;
    }

    int limit = 200;
    if (_twitter._limitName != "")
        limit =  std::stoi( _twitter._limitName );

    bool isWorking = _twitCurl.mentionsGet();
    std::string response = getWebResponse(isWorking);

    return json2TypeListOfTweetSelfMentioning(response, limit);
}

Twitter::type_tweet Twitter::postNewTweet() {
    assert(_twitter._crud == "post");
    if ( !isLogIn() ) {
        type_tweet tweet;
        tweet = std::make_pair("ERROR", "Bad Authentication data");
        return tweet;
    }

    bool isWorking = _twitCurl.statusUpdate(_twitter._actionName);
    std::string response = getWebResponse(isWorking);
    return json2TypeTweetpostNewTweet(response);
}

Twitter::type_tweet Twitter::deleteTweet() {
    assert(_twitter._crud == "delete");
    if ( !isLogIn() ) {
        type_tweet tweet;
        tweet = std::make_pair("ERROR", "Bad Authentication data");
        return tweet;
    }

    bool isWorking = _twitCurl.statusDestroyById(_twitter._actionName);
    std::string response = getWebResponse(isWorking);
    return json2TypeTweetDeletTweet(response);
}

std::vector<std::string> Twitter::getCurrentTrendWithLimit() {
    assert(_twitter._crud == "get");
    assert(_twitter._actionName == "trends");
    if ( !isLogIn() ) {
        return {"Bad Authentication data"};
    }

    int limit = 200;
    if (_twitter._limitName != "")
        limit =  std::stoi( _twitter._limitName );

    bool isWorking = _twitCurl.trendsCurrentGet();
    std::string response = getWebResponse(isWorking);
    return json2stringVecOfTrend(response, limit);
}


std::vector<std::string> Twitter::process() { //TODO: test in twitter_test.cpp

    if (_twitter._crud == "search") {
        return type_listOfTweet2VectorString(searchForTwitContainStringWithLimit(), "User");
    }

    if (_twitter._crud == "post") {
        return type_tweet2VectorString(postNewTweet(), "post");
    }

    if (_twitter._crud == "delete") {
        return type_tweet2VectorString(deleteTweet(), "delete");
    }

    if (_twitter._crud != "get") return {"Error, not a valid syntax use : get | post | delete | search"};

    if (_twitter._actionName == "mentions") {
        return type_listOfTweet2VectorString(getTwitSelfMentioningWithLimit(), "User");
    }

    if (_twitter._actionName == "trends")
        return getCurrentTrendWithLimit();

    return type_listOfTweet2VectorString(getTimeLineFromUserWithLimit(), "Id");
}

/////////////////////
///     PRIVATE   ///
/////////////////////

bool Twitter::isLogIn() {
    return _twitCurl.accountVerifyCredGet();
}

std::string Twitter::getWebResponse(bool isWorking) {
    std::string replyMsg;
    if( isWorking ) {
        _twitCurl.getLastWebResponse( replyMsg );
    }
    else {
        _twitCurl.getLastCurlError( replyMsg );
    }
    return replyMsg;
}

Twitter::type_listOfTweet Twitter::json2TypeListOfTweetGetTimeLine(std::string json) {
    std::stringstream ss;
    ss << json;
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);

    Twitter::type_listOfTweet listOfTweet;

    auto jsonP = nlohmann::json::parse(json);
    for(boost::property_tree::ptree::value_type &v : pt ){
        try {
            std::string key = v.second.get<std::string>("id");
            std::string value = v.second.get<std::string>("text");
            listOfTweet.push_back(std::make_pair(key, value));
        } catch (std::exception) {
            std::string key = "ERROR get timeline";
            listOfTweet.push_back(std::make_pair(key, jsonP.dump()));
            break;
        }

    }
    return listOfTweet;
}

Twitter::type_listOfTweet Twitter::json2TypeListOfTweetSearch(std::string json) {
    std::stringstream ss;
    ss << json;
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);

    Twitter::type_listOfTweet listOfTweet;

    auto jsonP = nlohmann::json::parse(json);
    try {
        for(boost::property_tree::ptree::value_type &v : pt.get_child("statuses") ){
            try {
                std::string key = v.second.get<std::string>("user.screen_name");
                std::string value = v.second.get<std::string>("text");
                listOfTweet.push_back(std::make_pair(key, value));
            } catch (std::exception) {
                std::string key = "ERROR search";
                listOfTweet.push_back(std::make_pair(key, jsonP.dump()));
                break;
            }
        }
    } catch (std::exception) {
    std::string key = "ERROR search";
    listOfTweet.push_back(std::make_pair(key, jsonP.dump()));
    }

    return listOfTweet;
}

Twitter::type_listOfTweet Twitter::json2TypeListOfTweetSelfMentioning(std::string json, int limit) {
    std::stringstream ss;
    ss << json;
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);

    Twitter::type_listOfTweet listOfTweet;

    auto jsonP = nlohmann::json::parse(json);
    for(boost::property_tree::ptree::value_type &v : pt ){
        try {
            std::string key = v.second.get<std::string>("user.screen_name");
            std::string value = v.second.get<std::string>("text");
            listOfTweet.push_back(std::make_pair(key, value));
        } catch (std::exception) {
            std::string key = "ERROR get mention";
            listOfTweet.push_back(std::make_pair(key, jsonP.dump()));
            break;
        }
        --limit;
        if (limit <= 0) break;
    }
    return listOfTweet;
}

Twitter::type_tweet Twitter::json2TypeTweetpostNewTweet(std::string json) {
    std::stringstream ss;
    ss << json;
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);

    Twitter::type_tweet tweet;
    auto jsonP = nlohmann::json::parse(json);
    try {
        std::string key = pt.get<std::string>("id");
        std::string value = pt.get<std::string>("text");
        tweet = std::make_pair(key, value);
    } catch (std::exception) {
        std::string key = "ERROR post new tweet";
        tweet = std::make_pair(key, jsonP.dump());
    }
    return tweet;
}

Twitter::type_tweet Twitter::json2TypeTweetDeletTweet(std::string json) {
    std::stringstream ss;
    ss << json;
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);

    Twitter::type_tweet tweet;
    auto jsonP = nlohmann::json::parse(json);
    try {
        std::string key = pt.get<std::string>("id");
        std::string value = pt.get<std::string>("text");
        tweet = std::make_pair(key, value);
    } catch (std::exception) {
        std::string key = "ERROR delete new tweet";
        tweet = std::make_pair(key, jsonP.dump());
    }
    return tweet;
}

std::vector<std::string> Twitter::json2stringVecOfTrend(std::string json, int limit) {
    std::stringstream ss;
    ss << json;
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);

    Twitter::type_tweet tweet;
    std::vector<std::string> outputTrend;
    try {
        auto jsonP = nlohmann::json::parse(json);
        nlohmann::json trends = jsonP.at("trends");

        for (auto trend : trends) {
            if (trend.is_array()) {
                for (auto tr : trend) {
                    outputTrend.push_back(tr.at("name"));
                    --limit;
                    if (limit <= 0) break;
                }
                break;
            }
        }
    } catch (std::exception) {
        outputTrend.push_back("ERROR get trends");
    }

    return outputTrend;
}

std::vector<std::string> Twitter::type_listOfTweet2VectorString(Twitter::type_listOfTweet listOfTweet, std::string keyName){
    std::vector<std::string> container;
    for (type_tweet tweet : listOfTweet) {
        std::string str("");
        str = keyName + " = " + tweet.first + " | tweet = " + tweet.second;
        container.push_back(str);
    }
    return container;
}

std::vector<std::string> Twitter::type_tweet2VectorString(Twitter::type_tweet tweet, std::string typeOperation){
    return {"The tweet " + tweet.first + " : " + tweet.second + " has been " + typeOperation};
}



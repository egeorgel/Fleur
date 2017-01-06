//
// Created by Edgar on 28/12/2016.
//

#include <gtest/gtest.h>
#include "service/Twitter.h"

class Twitter_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
        _twitCurl.getOAuth().setConsumerKey( "CBJimEZofmww7RQ4fvitrNHnj" );
        _twitCurl.getOAuth().setConsumerSecret( "M9NBXFAQLJC6j5lTcQ1QL0QMAm4L8nyCKGwNcARP5BGlrJaNLA" );
        _twitCurl.getOAuth().setOAuthTokenKey("2711422854-wV9d3fCBnyx7oTDFlRn9F4oCM4CysAaR97TeaKn");
        _twitCurl.getOAuth().setOAuthTokenSecret("qq9z0Bv5ZigB810CnRnF8rgrdx7cen9TS1CJTKlMngYRm");
    }

public:
    virtual ~Twitter_test() {}
    fleur::parser::Twitter _twitterParser;
    twitCurl _twitCurl;
};

TEST_F(Twitter_test, test_getTimeLineFromUser) {
    _twitterParser._crud = "get";
    _twitterParser._actionName = "*";
    _twitterParser._fromName = ".";

    fleur::Twitter twitterObjct(_twitterParser, _twitCurl);
    fleur::Twitter::type_listOfTweet listOfTweet = twitterObjct.getTimeLineFromUserWithLimit();
    ASSERT_EQ(listOfTweet.size(), 21);
    fleur::Twitter::type_tweet firstTwit = listOfTweet.back();
    ASSERT_EQ(firstTwit.first, "603949083192127489");
    ASSERT_EQ(firstTwit.second, "100 free awesome iOS tab bar &amp; toolbar icons by http://t.co/TWSAHVdNai");
}

TEST_F(Twitter_test, test_getTimeLineFromUserWithLimit) {
    _twitterParser._crud = "get";
    _twitterParser._actionName = "*";
    _twitterParser._fromName = ".";
    _twitterParser._limitName = "1";

    fleur::Twitter twitterObjct(_twitterParser, _twitCurl);
    fleur::Twitter::type_listOfTweet listOfTweet = twitterObjct.getTimeLineFromUserWithLimit();
    ASSERT_EQ(listOfTweet.size(), 1);
    fleur::Twitter::type_tweet firstTwit = listOfTweet.back();
    ASSERT_EQ(firstTwit.first, "814785277025779712");
    ASSERT_EQ(firstTwit.second, "Considering the development speed, when would I want to use Java instead of Python? by Garry Taylor https://t.co/NihLaoR6Eu");
}

TEST_F(Twitter_test, test_getTimeLineFromUserWithLimit_notLogIn) {
    _twitterParser._crud = "get";
    _twitterParser._actionName = "*";
    _twitterParser._fromName = ".";

    twitCurl twitCurl;
    fleur::Twitter twitterObjct(_twitterParser, twitCurl);
    fleur::Twitter::type_listOfTweet listOfTweet = twitterObjct.getTimeLineFromUserWithLimit();
    ASSERT_EQ(listOfTweet.size(), 1);
    fleur::Twitter::type_tweet firstTwit = listOfTweet.back();
    ASSERT_EQ(firstTwit.first, "ERROR get timeline");
    ASSERT_EQ(firstTwit.second, "{\"errors\":[{\"code\":215,\"message\":\"Bad Authentication data.\"}]}");
}

TEST_F(Twitter_test, test_searchForTwitContainStringWithLimit) {
    _twitterParser._crud = "search";
    _twitterParser._actionName = "the";
    _twitterParser._fromName = ".";
    _twitterParser._limitName = "4";

    fleur::Twitter twitterObjct(_twitterParser, _twitCurl);
    fleur::Twitter::type_listOfTweet listOfTweet = twitterObjct.searchForTwitContainStringWithLimit();
    ASSERT_EQ(listOfTweet.size(), 4);
}

TEST_F(Twitter_test, test_searchForTwitContainStringWithLimit_notLogIn) {
    _twitterParser._crud = "search";
    _twitterParser._actionName = "the";
    _twitterParser._fromName = ".";

    twitCurl twitCurl;
    fleur::Twitter twitterObjct(_twitterParser, twitCurl);
    fleur::Twitter::type_listOfTweet listOfTweet = twitterObjct.searchForTwitContainStringWithLimit();
    ASSERT_EQ(listOfTweet.size(), 1);
    fleur::Twitter::type_tweet firstTwit = listOfTweet.back();
    ASSERT_EQ(firstTwit.first, "ERROR search");
    ASSERT_EQ(firstTwit.second, "{\"errors\":[{\"code\":215,\"message\":\"Bad Authentication data.\"}]}");
}

TEST_F(Twitter_test, test_sgetTwitSelfMentioningWithLimit) {
    _twitterParser._crud = "get";
    _twitterParser._actionName = "mentions";
    _twitterParser._fromName = ".";
    _twitterParser._limitName = "2";

    fleur::Twitter twitterObjct(_twitterParser, _twitCurl);
    fleur::Twitter::type_listOfTweet listOfTweet = twitterObjct.getTwitSelfMentioningWithLimit();
    ASSERT_EQ(listOfTweet.size(), 2);
    ASSERT_EQ(listOfTweet[0].first, "JobProdDev");
    ASSERT_EQ(listOfTweet[0].second, "@EdgarGeorgel https://t.co/ZHIcy8zAuN : Bravo pour tes résultats sur le QCM Swift Niv.2 et ta 3è place aux… https://t.co/30Dj3W0UJZ");
    ASSERT_EQ(listOfTweet[1].first, "JobProdDev");
    ASSERT_EQ(listOfTweet[1].second, "@EdgarGeorgel https://t.co/ZHIcy8zAuN  Pour le moment tu fais partie du TOP100 des #BestCoders d'octobre sur+ de 1500 développeurs : BRAVO !");
}

TEST_F(Twitter_test, test_getTwitSelfMentioning) {
    _twitterParser._crud = "get";
    _twitterParser._actionName = "mentions";
    _twitterParser._fromName = ".";

    fleur::Twitter twitterObjct(_twitterParser, _twitCurl);
    fleur::Twitter::type_listOfTweet listOfTweet = twitterObjct.getTwitSelfMentioningWithLimit();
    ASSERT_EQ(listOfTweet.size(), 4);
    ASSERT_EQ(listOfTweet[0].first, "JobProdDev");
    ASSERT_EQ(listOfTweet[0].second, "@EdgarGeorgel https://t.co/ZHIcy8zAuN : Bravo pour tes résultats sur le QCM Swift Niv.2 et ta 3è place aux… https://t.co/30Dj3W0UJZ");
    ASSERT_EQ(listOfTweet[1].first, "JobProdDev");
    ASSERT_EQ(listOfTweet[1].second, "@EdgarGeorgel https://t.co/ZHIcy8zAuN  Pour le moment tu fais partie du TOP100 des #BestCoders d'octobre sur+ de 1500 développeurs : BRAVO !");
    ASSERT_EQ(listOfTweet[2].first, "Salim_NAHLE");
    ASSERT_EQ(listOfTweet[2].second, "@EdgarGeorgel @ValHook  @NicolasDonnaint  @syntecnumerique @IngenieursECE https://t.co/JPhEGIVYZy");
    ASSERT_EQ(listOfTweet[3].first, "Salim_NAHLE");
    ASSERT_EQ(listOfTweet[3].second, "Les @IngenieursECE présents pour #ledayclick. @EdgarGeorgel @NicolasDonnaint @ValHook https://t.co/cG8mp76k8C");
}

TEST_F(Twitter_test, test_getTwitSelfMentioningWithLimit_notLogIn) {
    _twitterParser._crud = "get";
    _twitterParser._actionName = "mentions";
    _twitterParser._fromName = ".";

    twitCurl twitCurl;
    fleur::Twitter twitterObjct(_twitterParser, twitCurl);
    fleur::Twitter::type_listOfTweet listOfTweet = twitterObjct.getTwitSelfMentioningWithLimit();
    ASSERT_EQ(listOfTweet.size(), 1);
    fleur::Twitter::type_tweet firstTwit = listOfTweet.back();
    ASSERT_EQ(firstTwit.first, "ERROR get mention");
    ASSERT_EQ(firstTwit.second, "{\"errors\":[{\"code\":215,\"message\":\"Bad Authentication data.\"}]}");
}


TEST_F(Twitter_test, test_postNewTwit_AND_delete) {
    _twitterParser._crud = "post";
    _twitterParser._actionName = "test post new tweet";

    fleur::Twitter twitterObjct(_twitterParser, _twitCurl);
    fleur::Twitter::type_tweet tweet = twitterObjct.postNewTweet();
    ASSERT_EQ(tweet.second, "test post new tweet");

    _twitterParser._crud = "delete";
    _twitterParser._actionName = tweet.first;
    fleur::Twitter twitterObjct2(_twitterParser, _twitCurl);
    fleur::Twitter::type_tweet tweet1 = twitterObjct2.deleteTweet();
    ASSERT_EQ(tweet.second, "test post new tweet");
}


TEST_F(Twitter_test, test_postNewTwit_notLogIn) {
    _twitterParser._crud = "post";
    _twitterParser._actionName = "test post new tweet";

    twitCurl twitCurl;
    fleur::Twitter twitterObjct(_twitterParser, twitCurl);
    fleur::Twitter::type_tweet tweet = twitterObjct.postNewTweet();
    ASSERT_EQ(tweet.first, "ERROR post new tweet");
}

TEST_F(Twitter_test, test_deletTwit_notLogIn) {
    _twitterParser._crud = "delete";
    _twitterParser._actionName = "324545664557676";

    twitCurl twitCurl;
    fleur::Twitter twitterObjct(_twitterParser, twitCurl);
    fleur::Twitter::type_tweet tweet = twitterObjct.deleteTweet();
    ASSERT_EQ(tweet.first, "ERROR delete new tweet");
}

TEST_F(Twitter_test, test_getCurrentTrendWithLimit) {
    _twitterParser._crud = "get";
    _twitterParser._actionName = "trends";
    _twitterParser._limitName = "4";
    fleur::Twitter twitterObjct(_twitterParser, _twitCurl);
    std::vector<std::string> trends = twitterObjct.getCurrentTrendWithLimit();
    ASSERT_EQ(trends.size(), 4);
}

TEST_F(Twitter_test, test_getCurrentTrendWithLimit_notLogin) {
    _twitterParser._crud = "get";
    _twitterParser._actionName = "trends";
    _twitterParser._limitName = "4";

    twitCurl twitCurl;
    fleur::Twitter twitterObjct(_twitterParser, twitCurl);
    std::vector<std::string> trends = twitterObjct.getCurrentTrendWithLimit();
    ASSERT_EQ(trends.size(), 1);
    ASSERT_EQ(trends[0], "ERROR get trends");
}
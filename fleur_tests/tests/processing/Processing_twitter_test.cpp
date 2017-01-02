//
// Created by Edgar on 02/01/2017.
//

#include <gtest/gtest.h>
#include "processing/Processing_twitter.h"

class Processing_twitter_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Processing_twitter_test() {}
    std::string _consumerKey = "CBJimEZofmww7RQ4fvitrNHnj";
    std::string _consumerSecret = "M9NBXFAQLJC6j5lTcQ1QL0QMAm4L8nyCKGwNcARP5BGlrJaNLA";
    std::string _tokenKey = "2711422854-wV9d3fCBnyx7oTDFlRn9F4oCM4CysAaR97TeaKn";
    std::string _tokenSecret = "qq9z0Bv5ZigB810CnRnF8rgrdx7cen9TS1CJTKlMngYRm";
};

TEST_F(Processing_twitter_test, get_tweets_from_twitter) {
    std::string requet("get tweets from twitter;");
    parser::Twitter twitter;
    parser::doParse(requet, twitter);

    Processing_twitter processingTwitter(twitter, _consumerKey, _consumerSecret, _tokenKey, _tokenSecret);
    std::vector<std::string> output = processingTwitter.build();
    ASSERT_EQ(output.size(), 21);
    ASSERT_EQ(output.back(), "Id = 603949083192127489 | tweet = 100 free awesome iOS tab bar &amp; toolbar icons by http://t.co/TWSAHVdNai");
}

TEST_F(Processing_twitter_test, get_tweets_from_twitter_limit_2) {
    std::string requet("get * from . limit 2;");
    parser::Twitter twitter;
    parser::doParse(requet, twitter);

    Processing_twitter processingTwitter(twitter, _consumerKey, _consumerSecret, _tokenKey, _tokenSecret);
    std::vector<std::string> output = processingTwitter.build();
    ASSERT_EQ(output.size(), 2);
    ASSERT_EQ(output.front(), "Id = 814785277025779712 | tweet = Considering the development speed, when would I want to use Java instead of Python? by Garry Taylor https://t.co/NihLaoR6Eu");
}

TEST_F(Processing_twitter_test, get_tweets_from_productHunt_limit_2) {
    std::string requet("get tweets from ProductHunt limit 2;");
    parser::Twitter twitter;
    parser::doParse(requet, twitter);

    Processing_twitter processingTwitter(twitter, _consumerKey, _consumerSecret, _tokenKey, _tokenSecret);
    std::vector<std::string> output = processingTwitter.build();
    ASSERT_EQ(output.size(), 2);
}

TEST_F(Processing_twitter_test, search_lol_from_twitter_limit_3) {
    std::string requet("search lol from * limit 3;");
    parser::Twitter twitter;
    parser::doParse(requet, twitter);

    Processing_twitter processingTwitter(twitter, _consumerKey, _consumerSecret, _tokenKey, _tokenSecret);
    std::vector<std::string> output = processingTwitter.build();
    ASSERT_EQ(output.size(), 3);
}

TEST_F(Processing_twitter_test, get_mentions_from) {
    std::string requet("get mentions from .;");
    parser::Twitter twitter;
    parser::doParse(requet, twitter);

    Processing_twitter processingTwitter(twitter, _consumerKey, _consumerSecret, _tokenKey, _tokenSecret);
    std::vector<std::string> output = processingTwitter.build();
    ASSERT_EQ(output.size(), 4);
    ASSERT_EQ(output[0], "User = JobProdDev | tweet = @EdgarGeorgel https://t.co/ZHIcy8zAuN : Bravo pour tes résultats sur le QCM Swift Niv.2 et ta 3è place aux… https://t.co/30Dj3W0UJZ");
    ASSERT_EQ(output[1], "User = JobProdDev | tweet = @EdgarGeorgel https://t.co/ZHIcy8zAuN  Pour le moment tu fais partie du TOP100 des #BestCoders d'octobre sur+ de 1500 développeurs : BRAVO !");
    ASSERT_EQ(output[2], "User = Salim_NAHLE | tweet = @EdgarGeorgel @ValHook  @NicolasDonnaint  @syntecnumerique @IngenieursECE https://t.co/JPhEGIVYZy");
    ASSERT_EQ(output[3], "User = Salim_NAHLE | tweet = Les @IngenieursECE présents pour #ledayclick. @EdgarGeorgel @NicolasDonnaint @ValHook https://t.co/cG8mp76k8C");
}

TEST_F(Processing_twitter_test, post_and_delete) {
    std::string requet("post test post new tweet;");
    parser::Twitter twitter;
    parser::doParse(requet, twitter);

    Processing_twitter processingTwitter(twitter, _consumerKey, _consumerSecret, _tokenKey, _tokenSecret);
    std::vector<std::string> output = processingTwitter.build();

    std::stringstream  stream(output[0]);
    std::string  word;
    stream >> word;  // word now holds 'The'
    stream >> word;  // word now holds 'tweet'
    stream >> word;  // word now holds 'id'

    ASSERT_EQ(output.size(), 1);
    ASSERT_EQ(output[0], "The tweet "+ word +" : test post new tweet has been post");

    std::string requet2("delete "+ word +";");
    parser::Twitter twitter2;
    parser::doParse(requet2, twitter2);

    Processing_twitter processingTwitter2(twitter2, _consumerKey, _consumerSecret, _tokenKey, _tokenSecret);
    std::vector<std::string> output2 = processingTwitter2.build();

    ASSERT_EQ(output2.size(), 1);
    ASSERT_EQ(output2[0], "The tweet "+ word +" : test post new tweet has been delete");
}

TEST_F(Processing_twitter_test, get_trends) {
    std::string requet("get trends;");
    parser::Twitter twitter;
    parser::doParse(requet, twitter);

    Processing_twitter processingTwitter(twitter, _consumerKey, _consumerSecret, _tokenKey, _tokenSecret);
    std::vector<std::string> output = processingTwitter.build();
}
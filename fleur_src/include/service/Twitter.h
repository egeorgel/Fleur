//
// Created by Edgar on 27/12/2016.
//

#ifndef FLEUR_TWITTER_H
#define FLEUR_TWITTER_H


#include "parser/Twitter_parser.h"

class Twitter {

public:
    typedef std::pair<std::string, std::string> type_tweet;
    typedef std::vector<type_tweet> type_listOfTweet ;
    Twitter(const parser::Twitter &twitter, twitCurl &twitCurl) : _twitter(twitter), _twitCurl(twitCurl){};
    ~Twitter(){}

    /*
     * return the time line (list of tweet) of the current user or the user give in the
     * parser::Twitter object the default limit is 200
     */
    type_listOfTweet getTimeLineFromUserWithLimit();

    /*
     * return a vector of pair the limit of the vector is fixe in the parse::Twitter object
     * key : user name
     * value : text of the tweet
     */
    type_listOfTweet searchForTwitContainStringWithLimit();

    /*
     * return all the tweet mentioning the connected acount
     */
    type_listOfTweet getTwitSelfMentioningWithLimit();

    /*
     * Post a new tweet on the connected user timeline
     */
    type_tweet postNewTweet();

    /*
     * Delete tweet from the connected user timeline
     */
    type_tweet deleteTweet();

    /*
     * return a vector of string containing the most tweet word of the moment
     */
    std::vector<std::string> getCurrentTrendWithLimit();

private:
    const parser::Twitter &_twitter;
    twitCurl &_twitCurl;

    bool isLogIn();
    std::string getWebResponse(bool isWorking);
    type_listOfTweet json2TypeListOfTweetGetTimeLine(std::string json);
    type_listOfTweet json2TypeListOfTweetSearch(std::string json);
    type_listOfTweet json2TypeListOfTweetSelfMentioning(std::string json, int limit);
    type_tweet json2TypeTweetpostNewTweet(std::string json);
    type_tweet json2TypeTweetDeletTweet(std::string json);
    std::vector<std::string> json2stringVecOfTrend(std::string json, int limit);

};


#endif //FLEUR_TWITTER_H

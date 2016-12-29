//
// Created by Edgar on 27/12/2016.
//

#ifndef FLEUR_TWITTER_H
#define FLEUR_TWITTER_H


#include "Twitter_parser.h"

class Twitter {

public:
    typedef std::vector<std::pair<std::string, std::string>> listOfTweet ;
    Twitter(const parser::Twitter & twitter) : _twitter(twitter){};

    /*
     * return the time line (list of tweet) of the current user or the user give in the
     * parser::Twitter object the default limit is 200
     */
    listOfTweet getTimeLineFromUserWithLimit() const;

    /*
     * return a vector of pair the limit of the vector is fixe in the parse::Twitter object
     * key : user name
     * value : text of the tweet
     */
    listOfTweet searchForTwitContainStringWithLimit() const;

    /*
     * return all the tweet mentioning the connected acount
     */
    listOfTweet getTwitSelfMentioningWithLimit() const;

    /*
     * Post a new tweet on the connected user timeline
     */
    void postNewTwit() const;

    /*
     * return a vector of string containing the most tweet word of the moment
     */
    std::vector<std::string> getCurrentTrendWithLimit() const;

private:
    parser::Twitter _twitter;
};


#endif //FLEUR_TWITTER_H

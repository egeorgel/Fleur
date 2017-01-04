//
// Created by Edgar on 02/01/2017.
//

#ifndef FLEUR_PROCESSING_TWITTER_H
#define FLEUR_PROCESSING_TWITTER_H


#include <service/Twitter.h>

class Processing_twitter {

public:
    typedef std::vector<std::string> Strings;

    Processing_twitter(const parser::Twitter &twitter, const parser::TwitterKeyOAut &twitterKeyOAut)
            : _twitterParser(twitter), _twitterKeyOAut(twitterKeyOAut){}

    /**
     * Run the _requete
     */
    Strings build();

private:
    parser::Twitter _twitterParser;
    parser::TwitterKeyOAut _twitterKeyOAut;
};

#endif //FLEUR_PROCESSING_TWITTER_H

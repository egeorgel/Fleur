//
// Created by Edgar on 02/01/2017.
//

#ifndef FLEUR_PROCESSING_TWITTER_H
#define FLEUR_PROCESSING_TWITTER_H


#include <service/Twitter.h>

class Processing_twitter {

public:
    typedef std::vector<std::string> Strings;

    Processing_twitter(const parser::Twitter &twitter,
                       const std::string &consumerKey, const std::string &consumerSecret,
                       const std::string &tokenKey, const std::string &tokenSecret)
            : _twitterParser(twitter),
              _consumerKey(consumerKey), _consumerSecret(consumerSecret),
              _tokenKey(tokenKey), _tokenSecret(tokenSecret){}

    /**
     * Run the _requete
     */
    Strings build();

private:
    parser::Twitter _twitterParser;
    std::string _consumerKey;
    std::string _consumerSecret;
    std::string _tokenKey;
    std::string _tokenSecret;
};

#endif //FLEUR_PROCESSING_TWITTER_H

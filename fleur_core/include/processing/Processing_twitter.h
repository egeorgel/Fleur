//
// Created by Edgar on 02/01/2017.
//

#ifndef FLEUR_PROCESSING_TWITTER_H
#define FLEUR_PROCESSING_TWITTER_H


#include <service/Twitter.h>

namespace fleur {
    class Processing_twitter {

    public:
        typedef std::vector<std::string> Strings;

        Processing_twitter(const fleur::parser::Twitter &twitter, const fleur::parser::TwitterKeyOAut &twitterKeyOAut)
                : _twitterParser(twitter), _twitterKeyOAut(twitterKeyOAut){}

        /**
         * Run the _requete
         */
        Strings build();

    private:
        fleur::parser::Twitter _twitterParser;
        fleur::parser::TwitterKeyOAut _twitterKeyOAut;
    };

}
#endif //FLEUR_PROCESSING_TWITTER_H

//
// Created by Val on 08/01/2017.
//

#ifndef FLEUR_PROCESSING_WOLFRAMALPHA_H
#define FLEUR_PROCESSING_WOLFRAMALPHA_H


#include <service/WolframAlpha.h>

namespace fleur {
    class Processing_wolframalpha {

    public:
        typedef std::vector<std::string> Strings;

        Processing_wolframalpha(const fleur::parser::WolframAlpha &wolframAlpha, const fleur::parser::WolframAlphaCredentials &wolframAlphaCredentials)
                : _wolframAlphaParser(wolframAlpha), _wolframAlphaCredentials(wolframAlphaCredentials){}

        /**
         * Run the _requete
         */
        Strings build();

    private:
        fleur::parser::WolframAlpha _wolframAlphaParser;
        fleur::parser::WolframAlphaCredentials _wolframAlphaCredentials;
    };

}


#endif //FLEUR_PROCESSING_WOLFRAMALPHA_H

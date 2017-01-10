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

        Processing_wolframalpha(const fleur::parser::WolframAlpha &wolframAlpha, const fleur::parser::WolframAlphaAppID &wolframAlphaAppID)
                : _wolframAlphaParser(wolframAlpha), _wolframAlphaAppID(wolframAlphaAppID){}

        /**
         * Run the _requete
         */
        Strings build();

    private:
        fleur::parser::WolframAlpha _wolframAlphaParser;
        fleur::parser::WolframAlphaAppID _wolframAlphaAppID;
    };

}


#endif //FLEUR_PROCESSING_WOLFRAMALPHA_H

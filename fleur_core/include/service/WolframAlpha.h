//
// Created by Val on 08/01/2017.
//

#ifndef FLEUR_WOLFRAMALPHA_H
#define FLEUR_WOLFRAMALPHA_H

#include "parser/WolframAlpha_parser.h"

namespace fleur {
    class WolframAlpha {

    public:

        WolframAlpha(const fleur::parser::WolframAlpha &wa_parser, const fleur::parser::WolframAlphaAppID &wa_appid)
                : _wolframAlphaParser(wa_parser), _wolframAlphaAppID(wa_appid) {};
        ~WolframAlpha(){};
        std::vector<std::string> process();

    private:
        const fleur::parser::WolframAlpha &_wolframAlphaParser;
        const fleur::parser::WolframAlphaAppID &_wolframAlphaAppID;
    };
}


#endif //FLEUR_WOLFRAMALPHA_H

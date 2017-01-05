//
// Created by Edgar on 04/01/2017.
//

#ifndef FLEUR_PROCESSING_WIKI_H
#define FLEUR_PROCESSING_WIKI_H


#include <service/Wiki.h>
namespace fleur {
    class Processing_wiki {

    public:
        typedef std::vector<std::string> Strings;

        Processing_wiki(const parser::Wiki &wiki) : _wikiParser(wiki) {}

        /**
         * Run the _requete
         */
        Strings build();

    private:
        parser::Wiki _wikiParser;
    };

}
#endif //FLEUR_PROCESSING_WIKI_H

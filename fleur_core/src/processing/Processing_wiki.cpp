//
// Created by Edgar on 04/01/2017.
//

#include "processing/Processing_wiki.h"

fleur::Processing_wiki::Strings fleur::Processing_wiki::build() {
    fleur::Wiki wiki(_wikiParser);
    return wiki.process();
}

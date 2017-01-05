//
// Created by Edgar on 04/01/2017.
//

#include "processing/Processing_wiki.h"

Processing_wiki::Strings Processing_wiki::build() {
    Wiki wiki(_wikiParser);
    return wiki.process();
}

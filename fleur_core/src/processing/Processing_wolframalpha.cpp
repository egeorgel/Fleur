//
// Created by Val on 09/01/2017.
//

#include "processing/Processing_wolframalpha.h"


fleur::Processing_wolframalpha::Strings fleur::Processing_wolframalpha::build() {
    WolframAlpha wa = WolframAlpha(_wolframAlphaParser);
    return wa.process();
}

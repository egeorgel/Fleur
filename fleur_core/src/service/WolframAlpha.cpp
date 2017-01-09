//
// Created by Val on 08/01/2017.
//


#include "service/WolframAlpha.h"

std::vector<std::string> fleur::WolframAlpha::process() {
    if (_wolframAlphaParser._action != "EVALUATE" && _wolframAlphaParser._action != "evaluate")
        return {"Error, not a valid syntax use : evaluate"};

    return {"denis"};
}
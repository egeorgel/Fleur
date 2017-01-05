//
// Created by Val on 04/01/2017.
//

#ifndef FLEUR_FLEUR_H
#define FLEUR_FLEUR_H


#include <iostream>
#include <string>

std::string fleur_version();

class Processing {

public:
    Processing(const std::string &requettes);

    typedef std::vector<std::string> Strings;
    Strings build();

private:

    typedef Strings type_requettes;
    type_requettes _requettes;

    bool postProcessingParssing(const std::string &requettes);
};

#endif //FLEUR_FLEUR_H

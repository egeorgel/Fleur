//
// Created by Edgar on 21/11/2016.
//

#ifndef FLEUR_PROCESSING_H
#define FLEUR_PROCESSING_H

#include "parser/Requete_parser.h"

class Processing {

public:
    typedef std::vector<std::string> Strings;

    Processing(const parser::Requete &requete) : _requete(requete) {}

    /**
     * Run the _requete
     */
    Strings build();

private:

    parser::Requete _requete;

    std::string processHeader(const std::string &format, const std::string &crud) const;
};


#endif //FLEUR_PROCESSING_H

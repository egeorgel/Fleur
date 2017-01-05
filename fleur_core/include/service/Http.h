//
// Created by Edgar on 06/11/2016.
//

#ifndef FLEUR_HTTP_H
#define FLEUR_HTTP_H

#include <string>
#include "parser/Requete_parser.h"

namespace fleur {
    class Http {

    public:
        Http(const fleur::parser::Requete & req) : _requete(req) {};

        std::string downloadContent() const;

        std::string get() const;

        std::string post() const;

        const fleur::parser::Requete &get_requete() const;

        std::string process() const;

    private:
        fleur::parser::Requete _requete;

        /*
         * Get parameters en create a string with format :
         *      name=daniel&project=curl
         */
        std::string type_parameterS2strFormat(const fleur::parser::type_parameterS &parameter) const;
    };


}
#endif //FLEUR_HTTP_H

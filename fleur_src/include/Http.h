//
// Created by Edgar on 06/11/2016.
//

#ifndef FLEUR_HTTP_H
#define FLEUR_HTTP_H

#include <string>
#include "Requete_parser.h"

class Http {

public:
    Http(const parser::Requete & req);

    ~Http();

    std::string downloadContent();

    std::string downloadJson();

    std::string get();

    std::string post();


    void *get_curl() const;
    const parser::Requete &get_requete() const;

private:
    void* _curl;
    parser::Requete _requete;

    /*
     * Get parameters en create a string with format :
     *      name=daniel&project=curl
     */
    std::string type_parameterS2strFormat(const parser::type_parameterS &parameter) const;
};


#endif //FLEUR_HTTP_H

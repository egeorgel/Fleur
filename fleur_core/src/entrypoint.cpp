//
// Created by Val on 04/01/2017.
//

#include <iostream>
#include <processing/Processing.h>

#define FLEUR_VERSION "1.0.0-alpha1"

std::string fleurql_version()
{
    return FLEUR_VERSION;
}

std::string fleurql_current_module() {
    return fleur::Processing::include;
}

std::string fleurql_installed_modules() {
    std::string ret = "";
    for (auto it : fleur::Processing::installed_modules)
        ret = ret + it.first + " - ";
    if (ret.size() < 3)
        return "";
    return ret.substr(0, ret.size()-3);
}

std::vector<std::string> fleurql_query(std::string requetes) {
    fleur::Processing processing(requetes);
    std::vector<std::string> results = processing.build();
    return results;
}
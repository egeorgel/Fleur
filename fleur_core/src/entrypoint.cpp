//
// Created by Val on 04/01/2017.
//

#include <iostream>
#include <vector>
#include <processing/Processing.h>
#define FLEUR_VERSION "1.0.0-alpha1"

std::string fleur_version()
{
    return FLEUR_VERSION;
}

std::vector<std::string> fleur_query(std::string requetes) {
    fleur::Processing processing(requetes);
    std::vector<std::string> results = processing.build();
    return results;
}
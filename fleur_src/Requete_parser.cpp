//
// Created by Edgar on 16/10/2016.
//

#include "Requete_parser.h"

/// PUBLIC

/**
 * string _parametersStr to type_parameterS _parameters
 */
void parser::Requete::splitParametersStr() {

    boost::erase_all(_parametersStr, " ");

    std::vector<std::string> parametersSplitByEgual = split(_parametersStr, ',');

    for (auto & element : parametersSplitByEgual) {
        std::vector<std::string> parameterIvect = split(element, '=');
        type_parameter parameter = std::make_pair(parameterIvect.front(), parameterIvect.back());
        _parameters.push_back(parameter);
    }
}

/// PRIVATE

/**
 * Split string by a delimiter
 * @param s
 * @param delim
 * @return
 */
std::vector<std::string> parser::Requete::split(const std::string &s, char delim) {
    std::stringstream stringstream;
    stringstream.str(s);
    std::string item;

    std::vector<std::string> parameters;
    while (std::getline(stringstream, item, delim)) {
        parameters.push_back(item);
    }
    return parameters;
}

//
// Created by Edgar on 16/10/2016.
//

#include "parser/Requete_parser.h"

/////////////////////
///     PUBLIC   ////
/////////////////////

/**
 * string _parametersStr to type_parameterS _parameters
 */
void fleur::parser::Requete::splitParametersStr(std::string &parameterStr, fleur::parser::type_parameterS &parameter) {

    boost::erase_all(parameterStr, " ");

    std::vector<std::string> parametersSplitByEgual = split(parameterStr, ',');

    for (auto &element : parametersSplitByEgual) {
        std::vector<std::string> parameterIvect = split(element, '=');
        type_parameter parameterTuple = std::make_pair(parameterIvect.front(), parameterIvect.back());
        parameter.push_back(parameterTuple);
    }
}


/////////////////////
///     PRIVATE   ///
/////////////////////

/**
 * Split string by a delimiter
 * @param s
 * @param delim
 * @return
 */
std::vector<std::string> fleur::parser::Requete::split(const std::string &s, char delim) {
    std::stringstream stringstream;
    stringstream.str(s);
    std::string item;

    std::vector<std::string> parameters;
    while (std::getline(stringstream, item, delim)) {
        parameters.push_back(item);
    }
    return parameters;
}

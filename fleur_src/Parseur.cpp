//
// Created by Edgar on 04/10/2016.
//

#include "Parseur.h"

const std::string &Parseur::get_input() const {
    return _input;
}

void Parseur::set_input(const std::string &_input) {
    Parseur::_input = _input;
}

Parseur::Parseur(const std::string &inputToParse) : _input(inputToParse){}
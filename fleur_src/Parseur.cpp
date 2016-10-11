//
// Created by Edgar on 04/10/2016.
//
#include <boost/tokenizer.hpp>
#include "Parseur.h"

using namespace boost;

Parseur::Parseur(const std::string &inputToParse) : _input(inputToParse){}

void Parseur::tokenize() {

    typedef tokenizer< char_separator<char> > tokenizer;

    char_separator<char> sep(" ");
    tokenizer tokens(_input, sep);

    if (tokens.begin() == "SELECT") {
        
    }
}



//// Getter && Setter ////

const std::string &Parseur::get_input() const {
    return _input;
}

void Parseur::set_input(const std::string &_input) {
    Parseur::_input = _input;
}


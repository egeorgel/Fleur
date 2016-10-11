//
// Created by Edgar on 04/10/2016.
//

#ifndef FLEUR_PARSEUR_H
#define FLEUR_PARSEUR_H


#include <string>

class Parseur {

private:
    std::string _input;
public:
    Parseur(const std::string &inputToParse);

    const std::string &get_input() const;
    void set_input(const std::string &_input);

    /*
     * splite _imput in word trying to find key word
     * raise exception if miss match
     */
    void tokenize();

};


#endif //FLEUR_PARSEUR_H

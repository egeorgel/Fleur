#include <iostream>

#include "Parseur.h"

int main() {

    std::string input = "";

    std::cout << "Enter query to parse : ";
    std::cin >> input;

    Parseur *parseur = new Parseur(input);

    std::cout << "Parsing : " << parseur->get_input() << std::endl;

    return 0;
}
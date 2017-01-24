//
// Created by Val on 04/01/2017.
//

#ifndef FLEUR_H
#define FLEUR_H


#include <iostream>
#include <string>

std::string fleur_version();
std::string fleur_current_module();
std::string fleur_installed_modules();
std::vector<std::string> fleur_query(std::string queries);

#endif //FLEUR_H

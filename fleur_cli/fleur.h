//
// Created by Val on 04/01/2017.
//

#ifndef FLEUR_H
#define FLEUR_H


#include <iostream>
#include <string>

std::string fleurql_version();
std::string fleurql_current_module();
std::string fleurql_installed_modules();
std::vector<std::string> fleurql_query(std::string queries);

#endif //FLEUR_FLEUR_H

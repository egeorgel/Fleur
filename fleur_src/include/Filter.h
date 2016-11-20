//
// Created by Edgar on 20/11/2016.
//

#ifndef FLEUR_FILTER_H
#define FLEUR_FILTER_H

#include <string>

class Filter {

public:
    Filter();

    //filter the result with the condition in  parser::Requete._selector
    std::vector<std::string> filterHTMLByMarked(const std::string &strToFilter, const std::string &marker);

private:
    std::vector<std::string> markerHtml;

};


#endif //FLEUR_FILTER_H

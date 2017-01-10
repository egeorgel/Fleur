//
// Created by Edgar on 02/01/2017.
//

#ifndef FLEUR_PROCESSING_H
#define FLEUR_PROCESSING_H

#include <vector>
#include <string>
#include <unordered_map>

namespace fleur {
    class Processing {

    public:
        Processing(const std::string &requettes);
        static std::string include;
        static std::unordered_map<std::string, bool> installed_modules;
        static std::unordered_map<std::string, std::string> modules_with_credentials;
        typedef std::vector<std::string> Strings;
        Strings build();

    private:

        typedef Strings type_requettes;
        type_requettes _requettes;

        bool postProcessingParssing(const std::string &requettes);
    };


}
#endif //FLEUR_PROCESSING_H

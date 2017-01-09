//
// Created by Edgar on 02/01/2017.
//

#include "processing/Processing.h"
#include "processing/Processing_http.h"
#include "ProcessingException.h"
#include "parser/Include_parser.h"
#include "processing/Processing_twitter.h"
#include "processing/Processing_wolframalpha.h"

#include <boost/algorithm/string.hpp>
#include <service/Wiki.h>
#include <processing/Processing_wiki.h>
#include <service/WolframAlpha.h>
#include <processing/Processing_wolframalpha.h>


std::string fleur::Processing::include = "";
std::unordered_map<std::string, bool> fleur::Processing::installed_modules {
        {"http", true},
        {"wikipedia", true},
        {"twitter", true},
        {"wolframalpha", true}
};




fleur::Processing::Processing(const std::string &requettes) {
    if (!fleur::Processing::postProcessingParssing(requettes)) {
        throw fleur::ProcessingException("Error in general syntax");
    }
}

fleur::Processing::Strings fleur::Processing::build() {
    assert(_requettes.size() > 0);

    fleur::parser::Include requeteInclude;
    fleur::parser::TwitterKeyOAut requeteTwitterKeyOAut;
    fleur::parser::WolframAlphaCredentials wolframAlphaCredentials;

    fleur::Processing::Strings output;
    bool isAfterUsing = false;

    for (std::string requetteStr : _requettes) {
        fleur::parser::Requete requeteHttp;
        fleur::parser::Twitter requeteTwitter;
        fleur::parser::Wiki requeteWiki;
        fleur::parser::WolframAlpha requeteWolframAlpha;
        fleur::parser::Include requeteInclude;
        Strings response;

        if (parser::doParse(requetteStr, requeteInclude)) { // INCLUDE
            std::string include_tolower = "";
            std::locale locale;
            for(auto elem : requeteInclude._module)
                include_tolower += std::tolower(elem,locale);
            // Check if the module is valid
            if (installed_modules[include_tolower] != true) {
                std::cerr << "No such module: " << include_tolower << std::endl;
                break;
            }
            isAfterUsing = true;
            include = requeteInclude._module;
            continue;
        }

        if (include == "http" && parser::doParse(requetteStr, requeteHttp)) { // HTTP
            fleur::Processing_http processing(requeteHttp);
            response = processing.build();
            output.insert(output.end(), response.begin(), response.end());
            continue;
        }

        if (include == "twitter" && isAfterUsing) { //KEY OAUTH TWITTER
            isAfterUsing = false;
            parser::doParse(requetteStr, requeteTwitterKeyOAut);
            continue;
        }

        if (requeteTwitterKeyOAut._consumerKey != "" && requeteTwitterKeyOAut._consumerSecret != "" &&
                requeteTwitterKeyOAut._tokenKey != "" && requeteTwitterKeyOAut._tokenSecret != "") { // TWITTER

            if (include == "twitter" && parser::doParse(requetteStr, requeteTwitter)) {
                fleur::Processing_twitter processing(requeteTwitter, requeteTwitterKeyOAut);
                response = processing.build();
                output.insert(output.end(), response.begin(), response.end());
                continue;
            }
        }

        if (include == "wikipedia") {
            if (fleur::parser::doParse(requetteStr, requeteWiki)) {
                fleur::Processing_wiki processing(requeteWiki);
                response = processing.build();
                output.insert(output.end(), response.begin(), response.end());
                continue;
            }
        }

        if (include == "wolframalpha") {
            if (fleur::parser::doParse(requetteStr, requeteWolframAlpha)) {
                fleur::Processing_wolframalpha processing(requeteWolframAlpha, wolframAlphaCredentials);
                response = processing.build();
                output.insert(output.end(), response.begin(), response.end());
                continue;
            }
        }

        std::cerr << "Invalid syntax" << std::endl;

    }

    return output;
}


bool fleur::Processing::postProcessingParssing(const std::string &requettes) {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    using ascii::space;
    using qi::_1;
    using qi::phrase_parse;
    using qi::char_;

    auto i_begin(std::begin(requettes)), i_end(std::end(requettes));
    bool r = qi::parse(i_begin, i_end,
            //  Begin grammar
                       (
                               +(char_ - ';') % ';'
                       ),
            //  End grammar
                       _requettes);

    for (int i = 0; i < _requettes.size(); ++i)
        _requettes[i] += ";";

    return r;
}

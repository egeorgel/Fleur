//
// Created by Edgar on 02/01/2017.
//

#include "processing/Processing.h"
#include "processing/Processing_http.h"
#include "ProcessingException.h"
#include "parser/Include_parser.h"
#include "processing/Processing_twitter.h"

#include <boost/algorithm/string.hpp>

Processing::Processing(const std::string &requettes) {

    if ( ! postProcessingParssing(requettes)) {
        throw ProcessingException("Error in general sintax");
    }


}


Processing::Strings Processing::build() {
    assert(_requettes.size() > 0);

    parser::Include requeteInclude;
    parser::TwitterKeyOAut requeteTwitterKeyOAut;

    Strings output;
    bool isAfterUsing = false;

    for (std::string requetteStr : _requettes) {
        parser::Requete requeteHttp;
        parser::Twitter requeteTwitter;
        Strings response;

        if (parser::doParse(requetteStr, requeteHttp)) { // HTTP
            Processing_http processing(requeteHttp);
            response = processing.build();
            output.insert(output.end(), response.begin(), response.end());
            continue;
        }

        if (parser::doParse(requetteStr, requeteInclude)) { // INCLUDE
            isAfterUsing = true;
            continue;
        }

        if (requeteInclude._module == "twitter" && isAfterUsing) { //KEY OAUTH
            isAfterUsing = false;
            parser::doParse(requetteStr, requeteTwitterKeyOAut);
            continue;
        }

        if (requeteTwitterKeyOAut._consumerKey != "" && requeteTwitterKeyOAut._consumerSecret != "" &&
                requeteTwitterKeyOAut._tokenKey != "" && requeteTwitterKeyOAut._tokenSecret != "") { // TWITTER
            if (parser::doParse(requetteStr, requeteTwitter)) {
                Processing_twitter processing(requeteTwitter, requeteTwitterKeyOAut);
                response = processing.build();
                output.insert(output.end(), response.begin(), response.end());
                continue;
            }
        }

    }

    return output;
}


bool Processing::postProcessingParssing(const std::string &requettes) {
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
                   +(char_ - ';')  % ';'
            )
            ,
            //  End grammar
            _requettes);

    for (int i = 0; i < _requettes.size(); ++i)
        _requettes[i] += ";";

    return r;
}


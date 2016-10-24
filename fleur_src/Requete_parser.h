//
// Created by Edgar on 16/10/2016.
//

#ifndef FLEUR_REQUETE_PARSER_H
#define FLEUR_REQUETE_PARSER_H

#include <iostream>
#include <complex>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include <boost/fusion/adapted.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_no_case.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

namespace parser {
    //  Requete struct
    typedef std::pair<std::string, std::string> type_parameter;
    typedef std::list<type_parameter> type_parameterS; // parameters are a list of tuple

    struct Requete {
        std::string _format;
        std::string _url;
        std::string _crud;
        //type_parameterS _parameters;
        std::string _parameters;
    };

}

// We need to tell fusion about our employee struct
// to make it a first-class fusion citizen. This has to
// be in global scope.
BOOST_FUSION_ADAPT_STRUCT(
        parser::Requete,
        (std::string, _format)
        (std::string, _url)
        (std::string, _crud)
        (std::string, _parameters)
)

namespace parser {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    // Requete parser
    template<typename Iterator>
    struct Requete_parser : qi::grammar<Iterator, Requete(), ascii::space_type> {

        qi::rule<Iterator, std::string(), ascii::space_type> lexemURL, lexemFormat, lexemCrud, lexemParameter;

        qi::rule<Iterator, std::string(), ascii::space_type> select  , from;
        qi::rule<Iterator, Requete(), ascii::space_type> requete;

        Requete_parser() : Requete_parser::base_type(requete) {
            using qi::lexeme;
            using ascii::char_;

            lexemURL = lexeme ['"' >> +(char_ - '"') >> '"'];
            lexemFormat = lexeme [+(char_("*jsonxmlhtJSONXMLHT"))];
            lexemCrud = lexeme [+(char_("*getposudlGETPOSUDL")) | ""];
            lexemParameter = lexeme[ ('(' >> +(char_ - ')') >> ')' ) | ""]; // (a=b, c=d)

            select  = ascii::no_case [ "select" ] >> lexemFormat ;
            from   = ascii::no_case [ "from" ]   >> lexemURL ;
            requete =  select >> from >> lexemCrud >> lexemParameter >> ';';
        }

    };

    template <typename C>
    bool doParse(const C& input, Requete &query) {
        auto i_begin(std::begin(input)), i_end(std::end(input));

        Requete_parser<decltype(i_begin)> requeteParser;

        try {
            bool ok = qi::phrase_parse(i_begin, i_end, requeteParser, ascii::space, query);
            if (ok) {
                std::cout << "parse success\n";
                std::cout << "format: " << query._format << "\n";
                std::cout << "url: " << query._url << "\n";
                std::cout << "crud: " << query._crud << "\n";
                std::cout << "parameter: " << query._parameters << "\n";
            }
            else {
                std::cerr << "parse failed: '" << std::string(i_begin, i_end) << "'\n";
            }
            return ok;
        } catch(const qi::expectation_failure<decltype(i_begin)>& e) {
            std::string frag(e.first, e.last);
            std::cerr << e.what() << "'" << frag << "'\n";
        }

        return false;
    }

}


#endif //FLEUR_REQUETE_PARSER_H

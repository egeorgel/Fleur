//
// Created by Edgar on 06/12/2016.
//

#ifndef FLEUR_REQUETETWIT_PARSER_H
#define FLEUR_REQUETETWIT_PARSER_H

#include <string>

#include <boost/algorithm/string.hpp>

#include <boost/fusion/adapted.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_no_case.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
namespace fleur {

    namespace parser {

        struct Include {

        public:
            std::string _module;
        };

    }
}


// We need to tell fusion about our Include struct
// to make it a first-class fusion citizen. This has to
// be in global scope.
BOOST_FUSION_ADAPT_STRUCT(
        fleur::parser::Include,
        (std::string, _module)
)

namespace fleur {

namespace parser {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    // Requete parser
    template<typename Iterator>
    struct Include_parser : qi::grammar<Iterator, Include(), ascii::space_type> {
        qi::rule<Iterator, Include(), ascii::space_type> requete;
        qi::rule<Iterator, std::string(), ascii::space_type> lexemModule;

        Include_parser() : Include_parser::base_type(requete) {
            using qi::lexeme;
            using ascii::char_;

            lexemModule = lexeme[+(char_ - ';') >> ';'];
            requete = ascii::no_case["use"] >> lexemModule;
        }

    };

    template<typename C>
    bool doParse(const C &input, Include &query) {
        auto i_begin(std::begin(input)), i_end(std::end(input));

        Include_parser<decltype(i_begin)> includeParser;

        try {
            bool ok = qi::phrase_parse(i_begin, i_end, includeParser, ascii::space, query);
            /*if (ok) {
                std::cout << "parse success\n";
                std::cout << "Using: " << query._module << "\n";
            } else {
                std::cerr << "parse failed: '" << std::string(i_begin, i_end) << "'\n";
            }*/
            return ok;
        } catch (const qi::expectation_failure<decltype(i_begin)> &e) {
            std::string frag(e.first, e.last);
            std::cerr << e.what() << "'" << frag << "'\n";
        }

        return false;
    }
}

}
#endif //FLEUR_REQUETETWIT_PARSER_H

//
// Created by Edgar on 03/01/2017.
//

#ifndef FLEUR_WIKI_PARSER_H
#define FLEUR_WIKI_PARSER_H

#include <string>

#include <boost/algorithm/string.hpp>

#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi_hold.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_no_case.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <twitcurl.h>

namespace parser {

    struct Wiki {

    public:
        std::string _crud; // find , get
        std::string _format; // text, html, header
        std::string _articleName;
        std::string _fromName;
        std::string _limit;

    private:

    };
}

// We need to tell fusion about our Wiki struct
// to make it a first-class fusion citizen. This has to
// be in global scope.
BOOST_FUSION_ADAPT_STRUCT(
        parser::Wiki,
        (std::string, _crud)
        (std::string, _format)
        (std::string, _articleName)
        (std::string, _fromName)
        (std::string, _limit)
)

namespace parser {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;


    // Requete parser
    template<typename Iterator>
    struct Wiki_parser : qi::grammar<Iterator, Wiki(), ascii::space_type> {
        qi::rule<Iterator, std::string(), ascii::space_type> lexemCrud, lexemFormat, lexemArticleName, lexemFromName, lexemLimitName;
        qi::rule<Iterator, Wiki(), ascii::space_type> requete;

        Wiki_parser() : Wiki_parser::base_type(requete) {
            using qi::lexeme;
            using ascii::char_;
            using qi::hold;

            lexemCrud = lexeme[+(char_("*getGETsearchSEARCH"))];
            lexemFormat = lexeme["(" >> (+(char_ - ")") >> ")")] | "" ;
            lexemArticleName = lexeme[(+(char_ - " from") >> " from")];
            lexemFromName = hold[lexeme[(+(char_ - " limit") >> " limit")]] | lexeme[(+(char_ - ";") >> ";")];
            lexemLimitName = lexeme[(+(char_ - ";") >> ";") | ""];

            requete = lexemCrud >> lexemFormat >> lexemArticleName >> lexemFromName >> lexemLimitName;
        }

    };

    template<typename C>
    bool doParse(const C &input, Wiki &query) {
        auto i_begin(std::begin(input)), i_end(std::end(input));

        Wiki_parser<decltype(i_begin)> twitterParser;

        try {
            bool ok = qi::phrase_parse(i_begin, i_end, twitterParser, ascii::space, query);
            if (ok) {
                std::cout << "parse success\n";
                std::cout << "action : " << query._crud << "\n";
                std::cout << "format : " << query._format << "\n";
                std::cout << "article : " << query._articleName << "\n";
                std::cout << "from : " << query._fromName << "\n";
                std::cout << "limit : " << query._limit << "\n";
            } else {
                std::cerr << "parse failed: '" << std::string(i_begin, i_end) << "'\n";
            }
            return ok;
        } catch (const qi::expectation_failure<decltype(i_begin)> &e) {
            std::string frag(e.first, e.last);
            std::cerr << e.what() << "'" << frag << "'\n";
        }
        return false;
    }
}


#endif //FLEUR_WIKI_PARSER_H

//
// Created by Edgar on 26/12/2016.
//

#ifndef FLEUR_TWITTER_PARSER_H
#define FLEUR_TWITTER_PARSER_H


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

namespace fleur {
    namespace parser {

        struct Twitter {

        public:
            std::string _crud; //get, post, search, delete
            std::string _actionName;
            std::string _fromName;
            std::string _limitName;
        };

        struct TwitterKeyOAut {

        public:
            std::string _consumerKey;
            std::string _consumerSecret;
            std::string _tokenKey;
            std::string _tokenSecret;
        };

    }
}

// We need to tell fusion about our Twitter struct
// to make it a first-class fusion citizen. This has to
// be in global scope.
BOOST_FUSION_ADAPT_STRUCT(
        fleur::parser::Twitter,
        (std::string, _crud)
                (std::string, _actionName)
                (std::string, _fromName)
                (std::string, _limitName)
)

BOOST_FUSION_ADAPT_STRUCT(
        fleur::parser::TwitterKeyOAut,
        (std::string, _consumerKey)
                (std::string, _consumerSecret)
                (std::string, _tokenKey)
                (std::string, _tokenSecret)
)

namespace fleur {
    namespace parser {
        namespace qi = boost::spirit::qi;
        namespace ascii = boost::spirit::ascii;


        // Requete parser
        template<typename Iterator>
        struct Twitter_parser : qi::grammar<Iterator, Twitter(), ascii::space_type> {
            qi::rule<Iterator, std::string(), ascii::space_type> lexemCrud, lexemActionName, lexemFromName, lexemLimitName;

            qi::rule<Iterator, std::string(), ascii::space_type> crud, from, limit;
            qi::rule<Iterator, Twitter(), ascii::space_type> requete;

            Twitter_parser() : Twitter_parser::base_type(requete) {
                using qi::lexeme;
                using ascii::char_;
                using qi::hold;

                lexemCrud = lexeme       [+(char_("*getposarchdlGETPOSARCHDL"))];
                lexemActionName = hold[ lexeme [ (+(char_ - " from") >> " from")  ] ]  | lexeme[ ( +(char_ - ";") >> ";" ) ];
                lexemFromName =   hold[ lexeme [ (+(char_ - " limit") >> " limit")] ]  | lexeme[ ( +(char_ - ";") >> ";" ) | "" ];
                lexemLimitName = lexeme  [ ( +(char_ - ";") >> ";" ) | ""];

                requete =  lexemCrud >> lexemActionName >> lexemFromName >> lexemLimitName;
            }

        };

        template <typename C>
        bool doParse(const C& input, Twitter &query) {
            auto i_begin(std::begin(input)), i_end(std::end(input));

            Twitter_parser<decltype(i_begin)> twitterParser;

            try {
                bool ok = qi::phrase_parse(i_begin, i_end, twitterParser, ascii::space, query);
                if (ok) {
                    std::cout << "parse success\n";
                    std::cout << "action : " << query._crud << "\n";
                    std::cout << "action name : " << query._actionName << "\n";
                    std::cout << "from : " << query._fromName << "\n";
                    std::cout << "limit : " << query._limitName << "\n";
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


        template<typename Iterator>
        struct TwitterKeyOAut_parser : qi::grammar<Iterator, TwitterKeyOAut(), ascii::space_type> {

            qi::rule<Iterator, std::string(), ascii::space_type> lexemConsumerKey, lexemConsumerSecret, lexemTokenKey, lexemTokenSecret;
            qi::rule<Iterator, TwitterKeyOAut(), ascii::space_type> requete;

            TwitterKeyOAut_parser() : TwitterKeyOAut_parser::base_type(requete) {
                using qi::lexeme;
                using ascii::char_;

                lexemConsumerKey = lexemConsumerSecret = lexemTokenKey = lexeme [ (+(char_ - ",") >> ",")  ];
                lexemTokenSecret = lexeme [ (+(char_ - ")") >> ")")  ];
                requete = "(" >> lexemConsumerKey >> lexemConsumerSecret >> lexemTokenKey >> lexemTokenSecret >> ";";

            }
        };

        template <typename C>
        bool doParse(const C& input, TwitterKeyOAut &query) {
            auto i_begin(std::begin(input)), i_end(std::end(input));

            TwitterKeyOAut_parser<decltype(i_begin)> twitterKeyOAutParser;

            try {
                bool ok = qi::phrase_parse(i_begin, i_end, twitterKeyOAutParser, ascii::space, query);
                if (ok) {
                    std::cout << "parse success\n";
                    std::cout << "consumerKey : " << query._consumerKey << "\n";
                    std::cout << "consumerSecret : " << query._consumerSecret << "\n";
                    std::cout << "tokenKey : " << query._tokenKey << "\n";
                    std::cout << "tokenSecret : " << query._tokenSecret << "\n";
                }
                else {
                    std::cout << "parse failed: '" << std::string(i_begin, i_end) << "'\n";
                }
                return ok;
            } catch(const qi::expectation_failure<decltype(i_begin)>& e) {
                std::string frag(e.first, e.last);
                std::cerr << e.what() << "'" << frag << "'\n";
            }
            return false;
        }

    }

}
#endif //FLEUR_TWITTER_PARSER_H

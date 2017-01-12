//
// Created by Val on 08/01/2017.
//

#ifndef FLEUR_WOLFRAMALPHA_PARSER_H
#define FLEUR_WOLFRAMALPHA_PARSER_H

#include <string>
#include <boost/algorithm/string.hpp>

#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi_hold.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_no_case.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

namespace fleur {
    namespace parser {

        struct WolframAlpha {

        public:
            std::string _action;
            std::string _to_evaluate;
        };

        struct WolframAlphaAppID {

        public:
            std::string _appID;
        };

    }
}

// We need to tell fusion about our Twitter struct
// to make it a first-class fusion citizen. This has to
// be in global scope.
BOOST_FUSION_ADAPT_STRUCT(
        fleur::parser::WolframAlpha,
        (std::string, _action)
        (std::string, _to_evaluate)
)

BOOST_FUSION_ADAPT_STRUCT(
        fleur::parser::WolframAlphaAppID,
(std::string, _appID)
)

namespace fleur {
    namespace parser {
        namespace qi = boost::spirit::qi;
        namespace ascii = boost::spirit::ascii;


        // Requete parser
        template<typename Iterator>
        struct WolframAlpha_parser : qi::grammar<Iterator, WolframAlpha(), ascii::space_type> {
            qi::rule<Iterator, std::string(), ascii::space_type> lexemEvaluate, lexemQuestion;
            qi::rule<Iterator, WolframAlpha(), ascii::space_type> requete;

            WolframAlpha_parser() : WolframAlpha_parser::base_type(requete) {
                using qi::lexeme;
                using ascii::char_;
                using qi::hold;

                lexemEvaluate = lexeme       [+(char_("*evaluateEVALUATE"))];
                lexemQuestion = lexeme  [ ( +(char_ - ";") >> ";" )];

                requete =  lexemEvaluate >> lexemQuestion;
            }

        };

        template <typename C>
        bool doParse(const C& input, WolframAlpha &query) {
            auto i_begin(std::begin(input)), i_end(std::end(input));

            WolframAlpha_parser<decltype(i_begin)> wolframalphaParser;

            try {
                bool ok = qi::phrase_parse(i_begin, i_end, wolframalphaParser, ascii::space, query);
                if (ok) {
                    std::cout << "parse success\n";
                    std::cout << "should evaluate : " << query._to_evaluate << "\n";
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


        template<typename Iterator>
        struct WolframAlphaAppID_parser : qi::grammar<Iterator, WolframAlphaAppID(), ascii::space_type> {

            qi::rule<Iterator, std::string(), ascii::space_type> lexemAppID;
            qi::rule<Iterator, WolframAlphaAppID(), ascii::space_type> requete;

            WolframAlphaAppID_parser() : WolframAlphaAppID_parser::base_type(requete) {
                using qi::lexeme;
                using ascii::char_;

                lexemAppID = lexeme  [ ( +(char_ - ";") >> ";" )];
                requete = lexemAppID;

            }
        };

        template <typename C>
        bool doParse(const C& input, WolframAlphaAppID &query) {
            auto i_begin(std::begin(input)), i_end(std::end(input));

            WolframAlphaAppID_parser<decltype(i_begin)> wolframAlphaAppIDParser;

            try {
                bool ok = qi::phrase_parse(i_begin, i_end, wolframAlphaAppIDParser, ascii::space, query);
                if (ok) {
                    std::cout << "parse success\n";
                    std::cout << "appID : " << query._appID << "\n";
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

}

#endif //FLEUR_WOLFRAMALPHA_PARSER_H

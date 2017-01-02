//
// Created by Edgar on 21/11/2016.
//

#ifndef FLEUR_XTML_PARSER_H
#define FLEUR_XTML_PARSER_H


#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace parserML {
    //  XML tree representation
    struct mini_xml;

    typedef boost::variant<boost::recursive_wrapper<mini_xml>, std::string> mini_xml_node;

    struct mini_xml {
        std::string name;                           // tag name / text
        std::vector<mini_xml_node> children;        // children
    };
}

// We need to tell fusion about our mini_xml struct
// to make it a first-class fusion citizen
BOOST_FUSION_ADAPT_STRUCT(
        parserML::mini_xml,
        (std::string, name)
        (std::vector<parserML::mini_xml_node>, children)
)

namespace parserML {
    namespace fusion = boost::fusion;
    namespace phoenix = boost::phoenix;
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    //  Print out the mini xml tree
    int const tabsize = 4;

    struct mini_xml_printer {
        mini_xml_printer(int indent = 0)
                : indent(indent) {}

        void operator()(mini_xml const& xml) const;

        int indent;
    };

    struct mini_xml_node_printer : boost::static_visitor<> {
        mini_xml_node_printer(int indent = 0)
                : indent(indent) {}

        void operator()(mini_xml const& xml) const;

        void operator()(std::string const& text) const;

        int indent;
    };


    struct  min_xml_geter{
        min_xml_geter(const std::string &tag, bool canUpdate) : _tag(tag), _canUpdateStrResult(canUpdate) {}

        std::vector<std::string> operator()(mini_xml const& xml);

        //static
        std::vector<std::string> _strResult;
        std::string _tag;
        bool _canUpdateStrResult;
    };
    //std::vector<std::string> min_xml_geter::_strResult = {};
    struct mini_xml_node_geter : boost::static_visitor<std::string> {
        mini_xml_node_geter(const std::string &tag, bool canUpdate) : _tag(tag), _canUpdateStrResult(canUpdate) {}

        std::string operator()(mini_xml const& xml) const;
        std::string operator()(std::string const& text) const;

        std::string _tag;
        bool _canUpdateStrResult;
    };





    ///  XML grammar definition
    template <typename Iterator>
    struct mini_xml_grammar : qi::grammar<Iterator, mini_xml(), qi::locals<std::string>, ascii::space_type> {
        mini_xml_grammar() : mini_xml_grammar::base_type(xml) {
            using qi::lit;
            using qi::lexeme;
            using ascii::char_;
            using ascii::string;
            using namespace qi::labels;

            using phoenix::at_c;
            using phoenix::push_back;

            text = lexeme[+(char_ - '<')        [_val += _1]];
            node = (xml | text)                 [_val = _1];

            start_tag =
                    '<'
                            >>  !lit('/')
                            >>  +(char_ - '>')
                            >>  '>'
                    ;

            end_tag =
                    "</"
                            >>  lexeme[+(char_ - '>')       [_val += _1]]
                            >>  '>'
                    ;

            doctype_tag = "<!"
                            >> +(char_ - '>')
                            >> '>'
                    ;

            mono_tag = "<"
                    >> +(char_ - ">")
                    >> "/>"
                    ;

            xml =   (doctype_tag | "")
                            >> start_tag
                            >>  *node                [push_back(at_c<1>(_val), _1)]
                            >>  end_tag             [at_c<0>(_val) = _1]
                    ;
        }

        qi::rule<Iterator, mini_xml(), qi::locals<std::string>, ascii::space_type> xml;
        qi::rule<Iterator, mini_xml_node(), ascii::space_type> node;
        qi::rule<Iterator, std::string(), ascii::space_type> text;
        qi::rule<Iterator, std::string(), ascii::space_type> start_tag, end_tag, doctype_tag, mono_tag;
    };

    template <typename C>
    bool doParse(const C& input, parserML::mini_xml &miniXml) {
        auto i_begin(std::begin(input)), i_end(std::end(input));

        typedef parserML::mini_xml_grammar<std::string::const_iterator> mini_xml_grammar;
        mini_xml_grammar xml; // Our grammar

        using boost::spirit::ascii::space;

        try {
            bool ok =  qi::phrase_parse(i_begin, i_end, xml, space, miniXml);
            if (ok) {
                std::cout << "-------------------------\n";
                std::cout << "Parsing succeeded\n";
                std::cout << "-------------------------\n";
                parserML::mini_xml_printer printer;
                printer(miniXml);

            }
            else {
                auto some = i_begin+30;
                std::string context(i_begin, (some>i_end)?i_end:some);
                std::cout << "-------------------------\n";
                std::cout << "Parsing failed\n";
                std::cout << "stopped at: \": " << context << "...\"\n";
                std::cout << "-------------------------\n";
            }
            return ok;
        } catch(const qi::expectation_failure<decltype(i_begin)>& e) {
            std::string frag(e.first, e.last);
            std::cerr << e.what() << "'" << frag << "'\n";
        }

        return false;
    }
}


#endif //FLEUR_XTML_PARSER_H

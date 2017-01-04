//
// Created by Edgar on 21/11/2016.
//

#include "parser/Xml_parser.h"

namespace parserML {

    void tab(int indent) {
        for (int i = 0; i < indent; ++i)
            std::cout << ' ';
    }


///////////////////////////////
///     mini_xml_printer    ///
///////////////////////////////

    void mini_xml_printer::operator()(mini_xml const& xml) const {
        tab(indent);
        std::cout << "tag: " << xml.name << std::endl;
        tab(indent);
        std::cout << '{' << std::endl;

        BOOST_FOREACH(mini_xml_node const& node, xml.children){
                        boost::apply_visitor(mini_xml_node_printer(indent), node);
                    }

        tab(indent);
        std::cout << '}' << std::endl;
    }

////////////////////////////////////
///     mini_xml_node_printer    ///
////////////////////////////////////

    void mini_xml_node_printer::operator()(mini_xml const& xml) const {
        mini_xml_printer(indent+tabsize)(xml);
    }

    void mini_xml_node_printer::operator()(std::string const& text) const {
        tab(indent+tabsize);
        std::cout << "text: \"" << text << '"' << std::endl;
    }

///////////////////////////////
///     min_xml_geter       ///
///////////////////////////////
    std::vector<std::string> min_xml_geter::operator()(mini_xml const& xml)  {
        if (_tag == xml.name) {
            _canUpdateStrResult = true;
        }
        for(mini_xml_node const& node : xml.children){
            std::string str = boost::apply_visitor(mini_xml_node_geter(_tag, _canUpdateStrResult), node);
            if (_canUpdateStrResult){
                //min_xml_geter::_strResult.push_back(str);
            }
        }
        return _strResult;  //min_xml_geter::_strResult;
    }

/////////////////////////////////////
///     mini_xml_node_geter       ///
/////////////////////////////////////
    std::string mini_xml_node_geter::operator()(mini_xml const& xml) const {
        min_xml_geter xml_geter(_tag, _canUpdateStrResult);
        xml_geter(xml);
        return xml.name;
    }

    std::string mini_xml_node_geter::operator()(std::string const& text) const {
        return text;
    }
}
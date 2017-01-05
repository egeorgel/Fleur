//
// Created by Edgar on 20/11/2016.
//
#include <algorithm>
#include <sstream>
#include <iostream>
#include "Filter.h"
#include "FilterException.h"

#include "Document.h"
#include "Node.h"

    Filter::Filter() {
        markerHtml = {
                "coments", // <!-- -->
                "a", "abbr", "address", "area", "article", "aside", "audio",
                "b", "base", "bdo", "bdi", "blockquote", "body", "br", "button",
                "canvas", "caption", "center", "cite", "code", "col", "colgroup", "command",
                "datalist", "dd", "del", "details", "dfn", "div", "dl", "dt",
                "em", "embed",
                "fieldset", "figcaption", "figure", "font", "footer",
                "h1", "h2", "h3", "h4", "h5", "h6", "head", "header", "hr", "html",
                "i", "iframe", "img", "input", "ins",
                "keygen", "kbd",
                "label", "legend", "li", "link",
                "main", "map", "mark", "menu", "meta", "meter",
                "nav", "noscript",
                "object", "ol", "optgroup", "option", "output",
                "p", "param", "pre", "progress",
                "q",
                "rp", "rt", "ruby",
                "s", "samp", "script", "section", "select", "small", "source", "span", "strong", "style", "sub",
                "summary", "sup",
                "table", "tbody", "td", "textarea", "tfoot", "th", "thead", "time", "title", "tr", "track",
                "ul",
                "var", "video",
                "wbr"
        };
    }


    std::vector<std::string> Filter::filterHTMLByMarked(const std::string &strToFilter, const std::string &markerStr) {

        std::string markerBuff = "";
        for (auto c : markerStr) {
            if (c == '.' || c == '[')
                break;
            markerBuff += c;
        }

        if (!(std::find(markerHtml.begin(), markerHtml.end(), markerBuff) != markerHtml.end()))
            throw FilterException("No valid html marker");

        std::vector<std::string> output;

        CDocument doc;
        doc.parse(strToFilter.c_str());
        CSelection c = doc.find(markerStr);

        int i = 0;

        while (i < c.nodeNum()) {
            std::cout << c.nodeAt(i).text().c_str() << std::endl;
            output.push_back(c.nodeAt(i).text().c_str());
            ++i;
        }

        return output;
    }



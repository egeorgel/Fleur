//
// Created by Edgar on 20/11/2016.
//
#include <algorithm>
#include <vector>
#include <sstream>
#include "Filter.h"
#include "FilterException.h"

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
            "s", "samp", "script", "section", "select", "small", "source", "span", "strong", "style", "sub", "summary", "sup",
            "table", "tbody", "td", "textarea", "tfoot", "th", "thead", "time", "title", "tr", "track",
            "ul",
            "var", "video",
            "wbr"
    };
}



std::vector<std::string> Filter::filterHTMLByMarked(const std::string &strToFilter, const std::string &markerStr) {

    if ( ! (std::find(markerHtml.begin(), markerHtml.end(), markerStr) != markerHtml.end()) )
        throw FilterException("No valid html marker");

    std::vector<std::string> output;
    std::string openMarker = "<" + markerStr + ">";
    std::string closingMarker = "</" + markerStr + ">";

    bool isRecording = false;
    std::string sentence = "";
    std::istringstream buf(strToFilter);

    for (std::string word; buf >> word;) {
        if (word == openMarker) {
            isRecording = true;
        } else if (word == closingMarker) {
            isRecording = false;
            output.push_back(sentence); // push the creating sentence in the vector at the end
            sentence = "";
        }

        if (isRecording && word != openMarker ) {
            sentence += " ";
            sentence += word;
        }
    }
    if (sentence != "") output.push_back(sentence);

    return output;
}





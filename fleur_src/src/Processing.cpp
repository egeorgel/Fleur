//
// Created by Edgar on 21/11/2016.
//

#include "Processing.h"
#include <assert.h>
#include <Http.h>
#include "Filter.h"

Processing::Strings Processing::build() {
    assert(_requete._url != "");

    Processing::Strings result;
    Http http(_requete);

    // 1 cheque the return format
    if (_requete._format == "html") {
        // 2 check if they are a crud method
        if (_requete._crud.empty()) {
            result.push_back(http.downloadContent());
        } else {
            result.push_back(processCrud("html"));
        }

    } else if (_requete._format == "json" ) {
        if (_requete._crud.empty()) {
            result.push_back(http.downloadJson());
        } else {
            result.push_back(processCrud("json"));
        }
    }
    //TODO: other format

    // 3 cheque if they are selector
    if (_requete._selector != "") {
        Filter filter;
        assert(result.size() == 1);
        if (_requete._format == "html") {
            result = filter.filterHTMLByMarked(result.front(), _requete._selector);
        }
    }

    return result;
}

std::string Processing::processCrud(const std::string &format) const {
    std::string result = "";

    if (_requete._crud == "get") {

    } else if (_requete._crud == "post") {

    } else if (_requete._crud == "delete") {

    }

    return result;
}

std::string Processing::processHeader(const std::string &format, const std::string &crud) const {
    std::string result = "";


    return result;
}

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
    result.push_back(http.process());

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

std::string Processing::processHeader(const std::string &format, const std::string &crud) const {
    std::string result = "";


    return result;
}

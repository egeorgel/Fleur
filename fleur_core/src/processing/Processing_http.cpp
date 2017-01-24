//
// Created by Edgar on 21/11/2016.
//

#include "processing/Processing.h"
#include "processing/Processing_http.h"
#include <assert.h>
#include <service/Http.h>
#include "Filter.h"

fleur::Processing_http::Strings fleur::Processing_http::build() {
    assert(_requete._url != "");

    fleur::Processing_http::Strings result;
    fleur::Http http(_requete);

    // 1 cheque the return format
    result.push_back(http.process());

    // 3 cheque if they are selector
    if (_requete._selector != "") {
        fleur::Filter filter;
        assert(result.size() == 1);
        if (_requete._format == "html") {
            result = filter.filterHTMLByMarked(result.front(), _requete._selector);
        }
    }

    return result;
}

std::string fleur::Processing_http::processHeader(const std::string &format, const std::string &crud) const {
    std::string result = "";
//TODO: a coder

    return result;
}

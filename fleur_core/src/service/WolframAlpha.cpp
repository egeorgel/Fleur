//
// Created by Val on 08/01/2017.
//

#include "service/WolframAlpha.h"
#include <cpr/cpr.h>
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>

std::vector<std::string> fleur::WolframAlpha::process() {
    if (_wolframAlphaParser._action != "EVALUATE" && _wolframAlphaParser._action != "evaluate")
        return {"Error, not a valid syntax use : evaluate"};

    auto r = cpr::Get(cpr::Url{"http://api.wolframalpha.com/v2/query"},
                      cpr::Parameters{{"input", _wolframAlphaParser._to_evaluate}, {"appid", _wolframAlphaAppID._appID}});

    if (r.status_code != 200)
        return {"Error, WolframAlpha API did not return a 200 HTTP Response"};

    boost::regex regex_err("<error>.*?<msg>(.*?)</msg>.*?</error>");
    boost::sregex_token_iterator iter_err(r.text.begin(), r.text.end(), regex_err, 1);
    boost::sregex_token_iterator end_err;
    if (iter_err != end_err)
        return {*iter_err};


    boost::regex regex("<plaintext>(.*?)</plaintext>");
    boost::sregex_token_iterator iter(r.text.begin(), r.text.end(), regex, 1);
    boost::sregex_token_iterator end;

    boost::regex regex2("<pod title='(.*?)'");
    boost::sregex_token_iterator iter2(r.text.begin(), r.text.end(), regex2, 1);
    boost::sregex_token_iterator end2;

    std::vector<std::string> results = std::vector<std::string>();
    for( ; iter != end && iter2 != end2; ++iter, ++iter2 )
        if (*iter != "") {
            std::string result = *iter2 + ": " + *iter;
            boost::replace_all(result, "&apos;", "'");
            boost::replace_all(result, "&quot;", "\"");
            results.push_back(result);
        }

    return results;
}
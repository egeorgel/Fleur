//
// Created by Edgar on 06/11/2016.
//

#include <HttpException.h>
#include "service/Http.h"

#include <cpr/cpr.h>
#include <json.hpp>

/////////////////////
///     PUBLIC   ////
/////////////////////

//TODO: Throw exception with result.status_code != 200

std::string fleur::Http::downloadContent() const {
    auto response = cpr::Get(cpr::Url{_requete._url});
    return response.text;
}

std::string fleur::Http::get() const {
    assert(!_requete._parameters.empty());
    assert(_requete._crud == "get");

    auto parameters = cpr::Parameters{{_requete._parameters}};
    auto result = cpr::Get(cpr::Url{_requete._url}, parameters);

    return result.text;
}

std::string fleur::Http::post() const {
    assert(!_requete._parameters.empty());
    assert(_requete._crud == "post");

    auto parameters = cpr::Payload{{_requete._parameters}};
    auto result = cpr::Post(cpr::Url{_requete._url}, parameters);

    return result.text;
}

std::string fleur::Http::process() const {
    if (_requete._crud == "") {
        return downloadContent();
    } else if (_requete._crud == "get") {
        return get();
    } else if (_requete._crud == "post") {
        return post();
    }

    //TODO: implement other crud methodes
    return "fleur::Http error";
}


/**
 * GETTER SETTER
 */
const fleur::parser::Requete &fleur::Http::get_requete() const {
    return _requete;
}



/////////////////////
///     PRIVATE   ///
/////////////////////

std::string fleur::Http::type_parameterS2strFormat(const fleur::parser::type_parameterS &parameter) const {
    std::string strOutput = "";
    for (auto &element : parameter)
        strOutput += element.first + "=" + element.second + "&";

    // Remove last &
    strOutput.pop_back();
    return strOutput;
}
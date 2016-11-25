//
// Created by Edgar on 06/11/2016.
//

#include <HttpException.h>
#include "Http.h"

#include <cpr/cpr.h>
#include <json.hpp>

/////////////////////
///     PUBLIC   ////
/////////////////////

//TODO: Throw exception with result.status_code != 200

std::string Http::downloadContent() {
    auto response = cpr::Get(cpr::Url{_requete._url});
    return response.text;
}

std::string Http::get() {
    assert( ! _requete._parameters.empty());
    assert(_requete._crud == "get");

    auto parameters = cpr::Parameters{{_requete._parameters}};
    auto result = cpr::Get(cpr::Url{_requete._url}, parameters);

    return result.text;
}

std::string Http::post() {
    assert( ! _requete._parameters.empty());
    assert(_requete._crud == "post");

    auto parameters = cpr::Payload{{_requete._parameters}};
    auto result = cpr::Post(cpr::Url{_requete._url}, parameters );

    return result.text;
}



/**
 * GETTER SETTER
 */
const parser::Requete &Http::get_requete() const {
    return _requete;
}



/////////////////////
///     PRIVATE   ///
/////////////////////

std::string Http::type_parameterS2strFormat(const parser::type_parameterS &parameter) const {
    std::string strOutput = "";
    for (auto & element : parameter)
        strOutput += element.first + "=" + element.second + "&";

    // Remove last &
    strOutput.pop_back();
    return strOutput;
}


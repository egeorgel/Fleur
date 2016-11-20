//
// Created by Edgar on 06/11/2016.
//

#include <HttpException.h>
#include <curl/curl.h>
#include "Http.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    std::string data((const char*) ptr, (size_t) size * nmemb);
    *((std::stringstream*) stream) << data << std::endl;
    return size * nmemb;
}


/////////////////////
///     PUBLIC   ////
/////////////////////

Http::Http(const parser::Requete & req) {
    if (req._url == "") //TODO: assert http format
        throw HttpException("Requete must have an url");

    _requete = req;

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    _curl = curl_easy_init();
}

Http::~Http() {
    curl_easy_cleanup(_curl);
    curl_global_cleanup();
}

std::string Http::downloadContent() {
    if (!_curl)
        throw HttpException("Error in curl_easy_init()");

    curl_easy_setopt(_curl, CURLOPT_URL, _requete._url.c_str());

    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1); //Prevent "longjmp causes uninitialized stack frame" bug
    curl_easy_setopt(_curl, CURLOPT_ACCEPT_ENCODING, "deflate");
    std::stringstream out;
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &out);

    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform(_curl);
    /* Check for errors */
    if (res != CURLE_OK)
        throw HttpException( std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res));

    return out.str();
}

std::string Http::downloadJson() {
    assert(_requete._format == "json");

    if (!_curl)
        throw HttpException("Error in curl_easy_init()");

    struct curl_slist *headers=NULL; // init to NULL is important
    curl_slist_append(headers, "Accept: application/json");
    curl_slist_append( headers, "Content-Type: application/json");
    curl_slist_append( headers, "charsets: utf-8");

    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(_curl, CURLOPT_URL, _requete._url.c_str());
    curl_easy_setopt(_curl, CURLOPT_HTTPGET,1);
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, headers);
    std::stringstream out;
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION,write_data);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &out);
    CURLcode res = curl_easy_perform(_curl);
    /* Check for errors */
    if (res != CURLE_OK)
        throw HttpException( std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res));

    return out.str();
}

std::string Http::get() {
    assert( ! _requete._parameters.empty());
    assert(_requete._crud == "get");

    if (!_curl)
        throw HttpException("Error in curl_easy_init()");

    std::string urlWithArg = _requete._url + "?" + type_parameterS2strFormat(_requete._parameters);
    curl_easy_setopt(_curl, CURLOPT_URL, urlWithArg.c_str());

    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1); //Prevent "longjmp causes uninitialized stack frame" bug
    curl_easy_setopt(_curl, CURLOPT_ACCEPT_ENCODING, "deflate");
    std::stringstream out;
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &out);

    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform(_curl);
    /* Check for errors */
    if (res != CURLE_OK)
        throw HttpException( std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res));

    return out.str();
}

std::string Http::post() {
    assert( ! _requete._parameters.empty());
    assert(_requete._crud == "post");

    if (!_curl)
        throw HttpException("Error in curl_easy_init()");

    curl_easy_setopt(_curl, CURLOPT_URL, _requete._url.c_str());
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, type_parameterS2strFormat(_requete._parameters).c_str());
    std::stringstream out;
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &out);
    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform(_curl);
    /* Check for errors */
    if(res != CURLE_OK)
        throw HttpException( std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res));

    return out.str();
}



/**
 * GETTER SETTER
 */
void *Http::get_curl() const {
    return _curl;
}

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

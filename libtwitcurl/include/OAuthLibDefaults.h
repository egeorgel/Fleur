//
// Created by Edgar on 27/12/2016.
//

#ifndef FLEUR_OAUTHLIBDEFAULTS_H
#define FLEUR_OAUTHLIBDEFAULTS_H

#include <string>

namespace oAuthLibDefaults
{
    /* Constants */
    const int OAUTHLIB_BUFFSIZE = 1024;
    const int OAUTHLIB_BUFFSIZE_LARGE = 1024;
    const std::string OAUTHLIB_CONSUMERKEY_KEY = "oauth_consumer_key";
    const std::string OAUTHLIB_CALLBACK_KEY = "oauth_callback";
    const std::string OAUTHLIB_VERSION_KEY = "oauth_version";
    const std::string OAUTHLIB_SIGNATUREMETHOD_KEY = "oauth_signature_method";
    const std::string OAUTHLIB_SIGNATURE_KEY = "oauth_signature";
    const std::string OAUTHLIB_TIMESTAMP_KEY = "oauth_timestamp";
    const std::string OAUTHLIB_NONCE_KEY = "oauth_nonce";
    const std::string OAUTHLIB_TOKEN_KEY = "oauth_token";
    const std::string OAUTHLIB_TOKENSECRET_KEY = "oauth_token_secret";
    const std::string OAUTHLIB_VERIFIER_KEY = "oauth_verifier";
    const std::string OAUTHLIB_SCREENNAME_KEY = "screen_name";
    const std::string OAUTHLIB_AUTHENTICITY_TOKEN_KEY = "authenticity_token";
    const std::string OAUTHLIB_SESSIONUSERNAME_KEY = "session[username_or_email]";
    const std::string OAUTHLIB_SESSIONPASSWORD_KEY = "session[password]";
    const std::string OAUTHLIB_AUTHENTICITY_TOKEN_TWITTER_RESP_KEY = "authenticity_token\" type=\"hidden\" value=\"";
    const std::string OAUTHLIB_TOKEN_TWITTER_RESP_KEY = "oauth_token\" type=\"hidden\" value=\"";
    const std::string OAUTHLIB_PIN_TWITTER_RESP_KEY = "code-desc\"><code>";
    const std::string OAUTHLIB_TOKEN_END_TAG_TWITTER_RESP = "\" />";
    const std::string OAUTHLIB_PIN_END_TAG_TWITTER_RESP = "</code>";

    const std::string OAUTHLIB_AUTHHEADER_STRING = "Authorization: OAuth ";
};

namespace oAuthTwitterApiUrls
{
    /* Twitter OAuth API URLs */
    const std::string OAUTHLIB_TWITTER_REQUEST_TOKEN_URL = "api.twitter.com/oauth/request_token";
    const std::string OAUTHLIB_TWITTER_AUTHORIZE_URL = "api.twitter.com/oauth/authorize?oauth_token=";
    const std::string OAUTHLIB_TWITTER_ACCESS_TOKEN_URL = "api.twitter.com/oauth/access_token";
};

#endif //FLEUR_OAUTHLIBDEFAULTS_H

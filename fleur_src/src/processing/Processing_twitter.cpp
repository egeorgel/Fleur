//
// Created by Edgar on 02/01/2017.
//

#include "processing/Processing_twitter.h"

Processing_twitter::Strings Processing_twitter::build() {

    twitCurl twitCurl;
    twitCurl.getOAuth().setConsumerKey( _consumerKey );
    twitCurl.getOAuth().setConsumerSecret( _consumerSecret );
    twitCurl.getOAuth().setOAuthTokenKey( _tokenKey );
    twitCurl.getOAuth().setOAuthTokenSecret( _tokenSecret );
    Twitter twitter(_twitterParser, twitCurl);

    return twitter.process();
}

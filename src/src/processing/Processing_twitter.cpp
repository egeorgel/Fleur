//
// Created by Edgar on 02/01/2017.
//

#include "processing/Processing_twitter.h"

Processing_twitter::Strings Processing_twitter::build() {

    twitCurl twitCurl;
    twitCurl.getOAuth().setConsumerKey( _twitterKeyOAut._consumerKey );
    twitCurl.getOAuth().setConsumerSecret( _twitterKeyOAut._consumerSecret );
    twitCurl.getOAuth().setOAuthTokenKey( _twitterKeyOAut._tokenKey );
    twitCurl.getOAuth().setOAuthTokenSecret( _twitterKeyOAut._tokenSecret );
    Twitter twitter(_twitterParser, twitCurl);

    return twitter.process();
}

//
// Created by Edgar on 27/12/2016.
//

#include <gtest/gtest.h>
#include "twitcurl.h"

class Libtwitcurl_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
        /* OAuth flow begins */
        /* Step 0: Set OAuth related params. These are got by registering your app at twitter.com */
        twitterObj.getOAuth().setConsumerKey( "CBJimEZofmww7RQ4fvitrNHnj" );
        twitterObj.getOAuth().setConsumerSecret( "M9NBXFAQLJC6j5lTcQ1QL0QMAm4L8nyCKGwNcARP5BGlrJaNLA" );
        twitterObj.getOAuth().setOAuthTokenKey("2711422854-wV9d3fCBnyx7oTDFlRn9F4oCM4CysAaR97TeaKn");
        twitterObj.getOAuth().setOAuthTokenSecret("qq9z0Bv5ZigB810CnRnF8rgrdx7cen9TS1CJTKlMngYRm");

        replyMsg = "";
    }

public:
    virtual ~Libtwitcurl_test() {}
    twitCurl twitterObj;
    std::string replyMsg;
};

TEST_F(Libtwitcurl_test, test_twitcurl_OAuth) {

    twitCurl twitterObjT;

    /* OAuth flow begins */
    /* Step 0: Set OAuth related params. These are got by registering your app at twitter.com */
    twitterObjT.getOAuth().setConsumerKey( "CBJimEZofmww7RQ4fvitrNHnj" );
    twitterObjT.getOAuth().setConsumerSecret( "M9NBXFAQLJC6j5lTcQ1QL0QMAm4L8nyCKGwNcARP5BGlrJaNLA" );
    twitterObjT.getOAuth().setOAuthTokenKey("2711422854-wV9d3fCBnyx7oTDFlRn9F4oCM4CysAaR97TeaKn");
    twitterObjT.getOAuth().setOAuthTokenSecret("qq9z0Bv5ZigB810CnRnF8rgrdx7cen9TS1CJTKlMngYRm");

    /* Account credentials verification */
    if( twitterObjT.accountVerifyCredGet() ) {
        twitterObjT.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else {
        twitterObjT.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
        FAIL();
    }
}

TEST_F(Libtwitcurl_test, test_twitcurl_statuses_public_timeline) {

    if( twitterObj.timelinePublicGet() ) {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
        FAIL();
    }
}

TEST_F(Libtwitcurl_test, test_twitcurl_statuses_friends_timeline) {

    if( twitterObj.timelineFriendsGet() ) {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
        FAIL();
    }
}

TEST_F(Libtwitcurl_test, test_twitcurl_statuses_user_timeline) {

    if( twitterObj.timelineUserGet(true, true, 3) ) {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
        FAIL();
    }
}

TEST_F(Libtwitcurl_test, test_twitcurl_statuses_user_timeline_productHunt) {

    if( twitterObj.timelineUserGet(true, true, 3, "ProductHunt") ) {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
        FAIL();
    }
}

TEST_F(Libtwitcurl_test, test_twitcurl_statuses_mention) {

    if( twitterObj.mentionsGet() ) {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
        FAIL();
    }
}

TEST_F(Libtwitcurl_test, test_twitcurl_statuses_friends) {

    if( twitterObj.friendsGet("EdgarGeorgel", false) ) {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
        FAIL();
    }
}

TEST_F(Libtwitcurl_test, test_twitcurl_statuses_follower) {

    if( twitterObj.followersGet("EdgarGeorgel", false) ) {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
        FAIL();
    }
}

TEST_F(Libtwitcurl_test, test_twitcurl_search) {

    if( twitterObj.search("love", "2") ) {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
        FAIL();
    }
}

TEST_F(Libtwitcurl_test, test_twitcurl_trends) {

    if( twitterObj.trendsCurrentGet() ) {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
        FAIL();
    }
}

TEST_F(Libtwitcurl_test, test_twitcurl_postNewStatus) {

    if( twitterObj.statusUpdate( "test new tweet" ) ) {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet web response:\n%s\n", replyMsg.c_str() );
    }
    else {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::accountVerifyCredGet error:\n%s\n", replyMsg.c_str() );
        FAIL();
    }
}

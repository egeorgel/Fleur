//
// Created by Edgar on 28/12/2016.
//

#include <gtest/gtest.h>
#include <Twitter.h>
#include <Include_parser.h>

class Twitter_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Twitter_test() {}
};

/**
 * Test + processu include
 */
TEST_F(Twitter_test, test_getTimeLineFromUserWithLimit) {

    parser::Twitter twitterParser;
    parser::Include includeParser;

    std::string inputInclude = "use twitter;";
    parser::doParse(inputInclude, includeParser);
    if (includeParser._module == "twitter") {
        // ask for twitter information

    }

}

//
// Created by Edgar on 20/11/2016.
//
#include <gtest/gtest.h>
#include "Filter.h"
#include "FilterException.h"

class Filter_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Filter_test(){}
};

TEST_F(Filter_test, filterHTMLByMarked_shouldThowException) {

    fleur::Filter filter;
    try {
        filter.filterHTMLByMarked("text", "NotAMarker");
        FAIL();
    }catch (const fleur::FilterException &e) {
        ASSERT_STREQ("No valid html marker", e.what());
    }
}

TEST_F(Filter_test, filterHTMLByMarked_divX1) {

    fleur::Filter filter;
    std::vector<std::string> outputFilter = filter.filterHTMLByMarked("<html> <h1> Test h1 </h1> <div> I'm a dive </div></html>",
                                                         "div");

    ASSERT_EQ(" I'm a dive ", outputFilter.front());
}

TEST_F(Filter_test, filterHTMLByMarked_pX3) {

    fleur::Filter filter;
    std::vector<std::string> outputFilter;
    outputFilter = filter.filterHTMLByMarked("<html> <h1> Test h1 </h1> "
                                             "<p> p marker 1 <span> spam moi </span> </p>"
                                             " <div> I'm a dive </div>"
                                             " <p> p marker 2 </p> "
                                             "<h1> Test h1 </h1> "
                                             "<p> p marker 3 </p> </html>", "p");
    std::vector<std::string> outputExpected = {" p marker 1  spam moi ", " p marker 2 ", " p marker 3 " };

    ASSERT_EQ(3, outputFilter.size());
    ASSERT_EQ(outputExpected.at(0), outputFilter.at(0));
    ASSERT_EQ(outputExpected.at(1), outputFilter.at(1));
    ASSERT_EQ(outputExpected.at(2), outputFilter.at(2));
}

TEST_F(Filter_test, filterHTMLcalss) {

    fleur::Filter filter;
    std::vector<std::string> outputFilter;
    outputFilter = filter.filterHTMLByMarked("<html> <h1 > Test h1 </h1> "
                                                     "<p> p marker 1 <span> spam moi </span> </p>"
                                                     " <div> I'm a dive </div>"
                                                     " <p class=\"chevre\"> p marker 2 </p> "
                                                     "<h1> Test h1 </h1> "
                                                     "<p class=\"chevre\"> p marker 3 </p> </html>", "p.chevre");
    std::vector<std::string> outputExpected = {" p marker 2 ", " p marker 3 " };
    std::cout << outputFilter.size() << std::endl;
    for (auto str : outputFilter)
        std::cout << str << std::endl;
    ASSERT_EQ(2, outputFilter.size());
    ASSERT_EQ(outputExpected.at(0), outputFilter.at(0));
    ASSERT_EQ(outputExpected.at(1), outputFilter.at(1));
}

TEST_F(Filter_test, filterHTMLid) {

    fleur::Filter filter;
    std::vector<std::string> outputFilter;
    outputFilter = filter.filterHTMLByMarked("<html> <h1 > Test h1 </h1> "
                                                     "<p> p marker 1 <span> spam moi </span> </p>"
                                                     " <div> I'm a dive </div>"
                                                     " <p class=\"chevre\"> p marker 2 </p> "
                                                     "<h1> Test h1 </h1> "
                                                     "<p id=\"chevre\"> p marker 3 </p> </html>", "p[id=\"chevre\"]");
    std::vector<std::string> outputExpected = {" p marker 3 " };
    std::cout << outputFilter.size() << std::endl;
    for (auto str : outputFilter)
        std::cout << str << std::endl;
    ASSERT_EQ(1, outputFilter.size());
    ASSERT_EQ(outputExpected.at(0), outputFilter.at(0));
}
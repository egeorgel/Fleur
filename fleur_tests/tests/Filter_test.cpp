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

    Filter filter;
    try {
        filter.filterHTMLByMarked("text", "NotAMarker");
        FAIL();
    }catch (const FilterException &e) {
        ASSERT_STREQ("No valid html marker", e.what());
    }
}

TEST_F(Filter_test, filterHTMLByMarked_divX1) {

    Filter filter;
    std::vector<std::string> outputFilter = filter.filterHTMLByMarked("<h1> Test h1 </h1> no marker <div> I'm a dive </div>",
                                                         "div");
    ASSERT_EQ(" I'm a dive", outputFilter.front());
}

TEST_F(Filter_test, filterHTMLByMarked_pX3) {

    Filter filter;
    std::vector<std::string> outputFilter;
    outputFilter = filter.filterHTMLByMarked("<h1> Test h1 </h1> "
                                             "<p> p marker 1 </p>"
                                             " <div> I'm a dive </div>"
                                             " <p> p marker 2 </p> "
                                             "<img src=\"img/toto.jpg\"/> "
                                             "<p> p marker 3 </p> ", "p");
    std::vector<std::string> outputExpected = {" p marker 1", " p marker 2", " p marker 3" };
    ASSERT_EQ(outputExpected, outputFilter);
}
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
    std::vector<std::string> outputFilter = filter.filterHTMLByMarked("<html> <h1> Test h1 </h1> <div> I'm a dive </div></html>",
                                                         "div");

    ASSERT_EQ(" I'm a dive ", outputFilter.front());
}

TEST_F(Filter_test, filterHTMLByMarked_pX3) {

    Filter filter;
    std::vector<std::string> outputFilter;
    outputFilter = filter.filterHTMLByMarked("<html> <h1> Test h1 </h1> "
                                             "<p> p marker 1 <span> spam moi </span> </p>"
                                             " <div> I'm a dive </div>"
                                             " <p> p marker 2 </p> "
                                             "<h1> Test h1 </h1> "
                                             "<p> p marker 3 </p> </html>", "p");
    std::vector<std::string> outputExpected = {" p marker 1  spam moi ", " p marker 2 ", " p marker 3 " };
    std::cout << outputFilter.size() << std::endl;
    for (auto str : outputFilter)
        std::cout << str << std::endl;
    ASSERT_EQ(outputExpected.at(0), outputFilter.at(0));
    ASSERT_EQ(outputExpected.at(1), outputFilter.at(1));
    ASSERT_EQ(outputExpected.at(2), outputFilter.at(2));
}
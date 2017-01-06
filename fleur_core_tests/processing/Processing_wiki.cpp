//
// Created by Edgar on 04/01/2017.
//
#include <gtest/gtest.h>
#include <service/Wiki.h>
#include <processing/Processing_wiki.h>
#include <utils/sha1.h>

class Processing_wiki_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Processing_wiki_test() {}
};

TEST_F(Processing_wiki_test, search_C_from_wiki_limit) {

    std::string requet("search c++ from wikipedia limit 4;");
    fleur::parser::Wiki wiki;
    fleur::parser::doParse(requet, wiki);

    fleur::Processing_wiki processingWiki(wiki);
    std::vector<std::string> output = processingWiki.build();

    ASSERT_EQ(output.size(), 4);
    ASSERT_EQ(output[0], " *** Wikipedia Title *** \\nC++\\n *** Wikipedia Content *** \\nC++ (pronounced cee plus plus, /ˈsiː plʌs plʌs/) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.");
    ASSERT_EQ(output[1], " *** Wikipedia Title *** \\nC++11\\n *** Wikipedia Content *** \\nC++11 is a version of the standard for the programming language C++. It was approved by International Organization for Standardization (ISO) on 12 August 2011, replacing C++03, superseded by C++14 on 18 August 2014 and later, by C++17, which is still under development.");
    ASSERT_EQ(output[2], " *** Wikipedia Title *** \\nC++14\\n *** Wikipedia Content *** \\nC++14 is a version of the standard for the programming language C++. It is intended to be a small extension over C++11, featuring mainly bug fixes and small improvements.");
    ASSERT_EQ(output[3], " *** Wikipedia Title *** \\nC++Builder\\n *** Wikipedia Content *** \\nC++Builder is a rapid application development (RAD) environment, originally developed by Borland and as of 2009 owned by Embarcadero Technologies, for writing programs in the C++ programming language targeting Windows NT (IA-32 and x64), OS X, iOS and Android.");
}

TEST_F(Processing_wiki_test, search_C_from_wiki) {

    std::string requet("search c++ from wikipedia;");
    fleur::parser::Wiki wiki;
    fleur::parser::doParse(requet, wiki);

    fleur::Processing_wiki processingWiki(wiki);
    std::vector<std::string> output = processingWiki.build();

    ASSERT_EQ(output.size(), 10);
    ASSERT_EQ(output[0], " *** Wikipedia Title *** \\nC++\\n *** Wikipedia Content *** \\nC++ (pronounced cee plus plus, /ˈsiː plʌs plʌs/) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.");
    ASSERT_EQ(output[1], " *** Wikipedia Title *** \\nC++11\\n *** Wikipedia Content *** \\nC++11 is a version of the standard for the programming language C++. It was approved by International Organization for Standardization (ISO) on 12 August 2011, replacing C++03, superseded by C++14 on 18 August 2014 and later, by C++17, which is still under development.");
    ASSERT_EQ(output[2], " *** Wikipedia Title *** \\nC++14\\n *** Wikipedia Content *** \\nC++14 is a version of the standard for the programming language C++. It is intended to be a small extension over C++11, featuring mainly bug fixes and small improvements.");
    ASSERT_EQ(output[3], " *** Wikipedia Title *** \\nC++Builder\\n *** Wikipedia Content *** \\nC++Builder is a rapid application development (RAD) environment, originally developed by Borland and as of 2009 owned by Embarcadero Technologies, for writing programs in the C++ programming language targeting Windows NT (IA-32 and x64), OS X, iOS and Android.");
}

TEST_F(Processing_wiki_test, get_header_c_from_wiki) {

    std::string requet("get (header) c++ from wikipedia;");
    fleur::parser::Wiki wiki;
    fleur::parser::doParse(requet, wiki);

    fleur::Processing_wiki processingWiki(wiki);
    std::vector<std::string> output = processingWiki.build();

    ASSERT_EQ(output.size(), 1);
    ASSERT_EQ(output[0], " *** Wikipedia Title *** \\nC++\\n *** Wikipedia Content *** \\nC++ (pronounced cee plus plus, /ˈsiː plʌs plʌs/) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.");
}

TEST_F(Processing_wiki_test, get_html_c_from_wiki) {

    std::string requet("get (html) C++ from wikipedia;");
    fleur::parser::Wiki wiki;
    fleur::parser::doParse(requet, wiki);

    fleur::Processing_wiki processingWiki(wiki);
    std::vector<std::string> output = processingWiki.build();

    ASSERT_EQ(output.size(), 1);
    std::string sha = sha1(output[0]);
    std::cout << output[0];
    ASSERT_EQ(sha, "03f6147d88bf6c3ad899b77939b6dd5fecf79423");
}

TEST_F(Processing_wiki_test, get_txt_c_from_wiki) {

    std::string requet("get (txt) c++ from wikipedia;");
    fleur::parser::Wiki wiki;
    fleur::parser::doParse(requet, wiki);

    fleur::Processing_wiki processingWiki(wiki);
    std::vector<std::string> output = processingWiki.build();

    ASSERT_EQ(output.size(), 1);
    std::string sha = sha1(output[0]);
    ASSERT_EQ(sha, "c4f1c0429633d0c68ceb15dcf23f87de890a921a");
}
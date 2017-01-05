//
// Created by Edgar on 03/01/2017.
//

#include <gtest/gtest.h>
#include <service/Wiki.h>
#include "utils/sha1.h"

class Wiki_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Wiki_test() {}
};

TEST_F(Wiki_test, findMostRelativeSubjectWithLimit_test) {

    parser::Wiki wikiParser;
    wikiParser._articleName = "C++";
    wikiParser._crud = "search";
    wikiParser._fromName = "wikipedia";

    Wiki wiki(wikiParser);
    Wiki::type_listArticle articles = wiki.findMostRelativeSubjectWithLimit();

    ASSERT_EQ(10, articles.size());
    ASSERT_EQ("C++", articles[0].first);
    ASSERT_EQ("C++ (pronounced cee plus plus, /ˈsiː plʌs plʌs/) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.",
              articles[0].second);
    ASSERT_EQ("C++11", articles[1].first);
    ASSERT_EQ("C++11 is a version of the standard for the programming language C++. It was approved by International Organization for Standardization (ISO) on 12 August 2011, replacing C++03, superseded by C++14 on 18 August 2014 and later, by C++17, which is still under development.",
                articles[1].second);
}

TEST_F(Wiki_test, findMostRelativeSubjectWithLimit_withLimit_test) {

    parser::Wiki wikiParser;
    wikiParser._articleName = "C++";
    wikiParser._crud = "search";
    wikiParser._fromName = "wikipedia";
    wikiParser._limit = "2";

    Wiki wiki(wikiParser);
    Wiki::type_listArticle articles = wiki.findMostRelativeSubjectWithLimit();

    ASSERT_EQ(2, articles.size());
    ASSERT_EQ("C++", articles[0].first);
    ASSERT_EQ("C++ (pronounced cee plus plus, /ˈsiː plʌs plʌs/) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.",
                articles[0].second);
    ASSERT_EQ("C++11", articles[1].first);
    ASSERT_EQ("C++11 is a version of the standard for the programming language C++. It was approved by International Organization for Standardization (ISO) on 12 August 2011, replacing C++03, superseded by C++14 on 18 August 2014 and later, by C++17, which is still under development.",
                 articles[1].second);
}

TEST_F(Wiki_test, getArticleHeader_test) {

    parser::Wiki wikiParser;
    wikiParser._articleName = "C++";
    wikiParser._crud = "get";
    wikiParser._fromName = "wikipedia";
    wikiParser._format = "header";

    Wiki wiki(wikiParser);
    Wiki::type_article article = wiki.getArticleHeader();

    ASSERT_EQ("C++", article.first);
    ASSERT_EQ("C++ (pronounced cee plus plus, /ˈsiː plʌs plʌs/) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.",
              article.second);
}


TEST_F(Wiki_test, getArticleHtml_test) {

    parser::Wiki wikiParser;
    wikiParser._articleName = "C++";
    wikiParser._crud = "get";
    wikiParser._fromName = "wikipedia";
    wikiParser._format = "html";

    Wiki wiki(wikiParser);
    Wiki::type_article article = wiki.getArticleHtml();

    ASSERT_EQ("C++", article.first);
    std::cout << article.second;
    std::string sha = sha1(article.second);
    ASSERT_EQ(sha, "a4494bcf3d5554ace2a30e0771362206b944504b");
}

TEST_F(Wiki_test, getArticleText_test) {

    parser::Wiki wikiParser;
    wikiParser._articleName = "C++";
    wikiParser._crud = "get";
    wikiParser._fromName = "wikipedia";
    wikiParser._format = "txt";

    Wiki wiki(wikiParser);
    Wiki::type_article article = wiki.getArticleText();

    ASSERT_EQ("C++", article.first);

    std::string sha = sha1(article.second);
    ASSERT_EQ(sha, "8110e3eb1e76ad54e34e8ff916e480f19ad82516");
}



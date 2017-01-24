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

    fleur::parser::Wiki wikiParser;
    wikiParser._articleName = "C++";
    wikiParser._crud = "search";
    wikiParser._fromName = "wikipedia";

    fleur::Wiki wiki(wikiParser);
    fleur::Wiki::type_listArticle articles = wiki.findMostRelativeSubjectWithLimit();

    ASSERT_EQ(10, articles.size());
    ASSERT_EQ("C++", articles[0].first);
    ASSERT_EQ("C++ (pronounced cee plus plus, /ˈsiː plʌs plʌs/) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.",
              articles[0].second);
    ASSERT_EQ("C++11", articles[1].first);
    ASSERT_EQ("C++11 is a version of the standard for the programming language C++. It was approved by International Organization for Standardization (ISO) on 12 August 2011, replacing C++03, superseded by C++14 on 18 August 2014 and later, by C++17, which is still under development.",
                articles[1].second);
}

TEST_F(Wiki_test, findMostRelativeSubjectWithLimit_withLimit_test) {

    fleur::parser::Wiki wikiParser;
    wikiParser._articleName = "C++";
    wikiParser._crud = "search";
    wikiParser._fromName = "wikipedia";
    wikiParser._limit = "2";

    fleur::Wiki wiki(wikiParser);
    fleur::Wiki::type_listArticle articles = wiki.findMostRelativeSubjectWithLimit();

    ASSERT_EQ(2, articles.size());
    ASSERT_EQ("C++", articles[0].first);
    ASSERT_EQ("C++ (pronounced cee plus plus, /ˈsiː plʌs plʌs/) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.",
                articles[0].second);
    ASSERT_EQ("C++11", articles[1].first);
    ASSERT_EQ("C++11 is a version of the standard for the programming language C++. It was approved by International Organization for Standardization (ISO) on 12 August 2011, replacing C++03, superseded by C++14 on 18 August 2014 and later, by C++17, which is still under development.",
                 articles[1].second);
}

TEST_F(Wiki_test, getArticleHeader_test) {

    fleur::parser::Wiki wikiParser;
    wikiParser._articleName = "C++";
    wikiParser._crud = "get";
    wikiParser._fromName = "wikipedia";
    wikiParser._format = "header";

    fleur::Wiki wiki(wikiParser);
    fleur::Wiki::type_article article = wiki.getArticleHeader();

    ASSERT_EQ("C++", article.first);
    ASSERT_EQ("C++ (pronounced cee plus plus, /ˈsiː plʌs plʌs/) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.",
              article.second);
}


TEST_F(Wiki_test, getArticleHtml_test) {

    fleur::parser::Wiki wikiParser;
    wikiParser._articleName = "C++";
    wikiParser._crud = "get";
    wikiParser._fromName = "wikipedia";
    wikiParser._format = "html";

    fleur::Wiki wiki(wikiParser);
    fleur::Wiki::type_article article = wiki.getArticleHtml();

    ASSERT_EQ("C++", article.first);
    std::cout << article.second;
    std::string sha = sha1(article.second);
    ASSERT_EQ(sha, "c3bb3dd1fcc60087d6271d44a06494c61764b9ea");
}

TEST_F(Wiki_test, getArticleText_test) {

    fleur::parser::Wiki wikiParser;
    wikiParser._articleName = "C++";
    wikiParser._crud = "get";
    wikiParser._fromName = "wikipedia";
    wikiParser._format = "txt";

    fleur::Wiki wiki(wikiParser);
    fleur::Wiki::type_article article = wiki.getArticleText();

    ASSERT_EQ("C++", article.first);

    std::string sha = sha1(article.second);
    ASSERT_EQ(sha, "b2bd688e3fe3414a0c621edbc121c4fd07c9da51");
}



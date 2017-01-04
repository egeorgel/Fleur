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
    ASSERT_EQ("<p><b>C++</b> (pronounced <i>cee plus plus</i>, <span><span>/<span><span title=\"/\xCB\x88/ primary stress follows\">\xCB\x88</span><span title=\"'s' in 'sigh'\">s</span><span title=\"/i\xCB\x90/ long 'e' in 'seed'\">i\xCB\x90</span></span> <span><span title=\"'p' in 'pie'\">p</span><span title=\"'l' in 'lie'\">l</span><span title=\"/\xCA\x8C/ short 'u' in 'bud'\">\xCA\x8C</span><span title=\"'s' in 'sigh'\">s</span></span> <span><span title=\"'p' in 'pie'\">p</span><span title=\"'l' in 'lie'\">l</span><span title=\"/\xCA\x8C/ short 'u' in 'bud'\">\xCA\x8C</span><span title=\"'s' in 'sigh'\">s</span></span>/</span></span>) is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation.</p>\n<p>It was designed with a bias toward system programming and embedded, resource-constrained and large systems, with performance, efficiency and flexibility of use as its design highlights. C++ has also been found useful in many other contexts, with key strengths being software infrastructure and resource-constrained applications, including desktop applications, servers (e.g. e-commerce, web search or SQL servers), and performance-critical applications (e.g. telephone switches or space probes). C++ is a compiled language, with implementations of it available on many platforms and provided by various organizations, including the Free Software Foundation (FSF's GCC), LLVM, Microsoft, Intel and IBM.</p>\n<p>C++ is standardized by the International Organization for Standardization (ISO), with the latest standard version ratified and published by ISO in December 2014 as <i>ISO/IEC 14882:2014</i> (informally known as C++14). The C++ programming language was initially standardized in 1998 as <i>ISO/IEC 14882:1998</i>, which was then amended by the C++03, <i>ISO/IEC 14882:2003</i>, standard. The current C++14 standard supersedes these and C++11, with new features and an enlarged standard library. Before the initial standardization in 1998, C++ was developed by Bjarne Stroustrup at Bell Labs since 1979, as an extension of the C language as he wanted an efficient and flexible language similar to C, which also provided high-level features for program organization.</p>\n<p>Many other programming languages have been influenced by C++, including C#, D, Java, and newer versions of C (after 1998).</p>\n<p></p>",
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

    std::string sha = sha1(article.second);
    ASSERT_EQ(article.second, "a4494bcf3d5554ace2a30e0771362206b944504b");
}

TEST_F(Wiki_test, getArticleText_test) {

    parser::Wiki wikiParser;
    wikiParser._articleName = "C++";
    wikiParser._crud = "get";
    wikiParser._fromName = "wikipedia";
    wikiParser._format = "txt";

    Wiki wiki(wikiParser);
    Wiki::type_article article = wiki.getArticleText();

    std::cout << article.second;
    ASSERT_EQ("C++", article.first);

    std::string sha = sha1(article.second);
    ASSERT_EQ(article.second, "8110e3eb1e76ad54e34e8ff916e480f19ad82516");
}



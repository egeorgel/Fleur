//
// Created by Edgar on 03/01/2017.
//

#ifndef FLEUR_WIKI_H
#define FLEUR_WIKI_H


#include <parser/Wiki_parser.h>
#include <cpr/response.h>
#include "Document.h"
#include "Node.h"

class Wiki {

public:
    typedef std::pair<std::string, std::string> type_article;
    typedef std::vector<type_article> type_listArticle;

    Wiki(const parser::Wiki &wiki) : _wiki(wiki), _urlApi("http://en.wikipedia.org/w/api.php") {}

    /*
     * Search an article, return most relative subject with limit
     */
    type_listArticle findMostRelativeSubjectWithLimit() const;

    /*
     * Search an article, return the header of the article
     */
    type_article getArticleHeader() const;

    /*
     * Search an article, return the article Html format
     */
    type_article getArticleHtml() const;

    /*
     * Search an article, return the article text format
     */
    type_article getArticleText() const;

private:

    parser::Wiki _wiki;
    std::string _urlApi;

    type_listArticle populatListArctivle(const std::string &limit, const cpr::Response &result) const;
    type_article populatArctivleHeader(const cpr::Response &result) const;
    type_article getUrlArticle(const cpr::Response &result) const;
};


#endif //FLEUR_WIKI_H

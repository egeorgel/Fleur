//
// Created by Edgar on 04/10/2016.
//

#include "gtest/gtest.h"
#include "Parseur.h"


class ParserTest : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~ParserTest() {}
};

TEST_F(ParserTest, parseur_SELECT_FROM_DENIS) {
    Parseur parseur("SELECT * FROM http://www.denis.fr/societe/");
    parseur.tokenize();
    EXPECT_EQ(parseur.get_input(), "Denis");
}


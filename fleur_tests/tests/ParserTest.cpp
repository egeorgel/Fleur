//
// Created by Edgar on 04/10/2016.
//

#include "gtest/gtest.h"
#include "Parseur.h"

#define TEST__PARSEUR_INPUT "Denis"

class ParserTest : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    ParserTest() : Test() {
        _parser = new Parseur(TEST__PARSEUR_INPUT);
    }

    virtual ~ParserTest() {
        delete _parser;
    }

    Parseur *_parser;
};

TEST_F(ParserTest, parseur_constructor_test) {
    EXPECT_EQ(_parser->get_input(), TEST__PARSEUR_INPUT);
}

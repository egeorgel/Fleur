//
// Created by Edgar on 02/01/2017.
//
#include <gtest/gtest.h>
#include "processing/Processing.h"

class Processing_test : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    virtual ~Processing_test() {}
};


TEST_F(Processing_test, test) {

    std::string requettes(  "select html from \"http://httpbin.org/html\";"
                            "select html (h1) from \"http://httpbin.org/html\";"
                            "using twitter;"
                            "(CBJimEZofmww7RQ4fvitrNHnj, M9NBXFAQLJC6j5lTcQ1QL0QMAm4L8nyCKGwNcARP5BGlrJaNLA, 2711422854-wV9d3fCBnyx7oTDFlRn9F4oCM4CysAaR97TeaKn, qq9z0Bv5ZigB810CnRnF8rgrdx7cen9TS1CJTKlMngYRm);"
                            "get * from . limit 2;");
}
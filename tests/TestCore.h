#pragma once

#include "main-test.h"

class TestCore: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestCore);
    CPPUNIT_TEST(testBase);
    CPPUNIT_TEST_SUITE_END();

public:
    TestCore();

    void testBase();
};


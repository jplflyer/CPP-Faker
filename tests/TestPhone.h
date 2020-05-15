#pragma once

#include "main-test.h"

class TestPhone: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestPhone);
    CPPUNIT_TEST(testPhoneNumber);
    CPPUNIT_TEST_SUITE_END();

public:
    TestPhone();

    void testPhoneNumber();
};


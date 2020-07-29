#pragma once

#include "main-test.h"

class TestAddress: public CppUnit:: TestFixture
{
    CPPUNIT_TEST_SUITE(TestAddress);
    CPPUNIT_TEST(testSimple);
    CPPUNIT_TEST(testFullAddress);
    CPPUNIT_TEST_SUITE_END();

public:
    // This runs all the simple tests to verify data seems fine.
    void testSimple();
    void testFullAddress();
};

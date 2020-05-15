#pragma once

#include "main-test.h"

class TestNumber: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestNumber);
    CPPUNIT_TEST(testNumber);
    CPPUNIT_TEST(testLeadingZeroNumber);
    CPPUNIT_TEST(testDecimalPart);
    CPPUNIT_TEST(testDecimal);
    CPPUNIT_TEST(testNonZeroDigit);
    CPPUNIT_TEST(testDigit);
    CPPUNIT_TEST(testHexadecimal);
    CPPUNIT_TEST(testNormal);
    CPPUNIT_TEST(testBetween);
    CPPUNIT_TEST_SUITE_END();

public:
    TestNumber();

    void testNumber();
    void testLeadingZeroNumber();
    void testDecimalPart();
    void testDecimal();
    void testNonZeroDigit();
    void testDigit();
    void testHexadecimal();
    void testNormal();
    void testBetween();
};


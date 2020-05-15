#pragma once

#include "main-test.h"

class TestName: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestName);
    CPPUNIT_TEST(testName);
    CPPUNIT_TEST(testNameWithMiddle);
    CPPUNIT_TEST(testMaleFirstName);
    CPPUNIT_TEST(testFemaleFirstName);
    CPPUNIT_TEST(testLastName);
    CPPUNIT_TEST(testPrefix);
    CPPUNIT_TEST(testSuffix);
    CPPUNIT_TEST(testInitials);
    CPPUNIT_TEST_SUITE_END();

public:
    TestName();
    void testName();
    void testNameWithMiddle();
    void testMaleFirstName();
    void testFemaleFirstName();
    void testLastName();
    void testPrefix();
    void testSuffix();
    void testInitials();
};

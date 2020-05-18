#include <iostream>

#include <faker/Name.h>
#include <faker/Company.h>

#include "TestCore.h"

using std::cout;
using std::endl;
using std::string;

string TEST_NAME = "TestCore";

CPPUNIT_TEST_SUITE_REGISTRATION(TestCore);

TestCore::TestCore()
{
    Faker::Base::setConfigDir("./locales");
}

/**
 * This does a very simple check that the library works.
 */
void
TestCore::testBase() {
    string name = Faker::Name::name();
    CPPUNIT_ASSERT_GREATER_MESSAGE("We expected something useful", 0, static_cast<int>(name.length()) );
}


/**
 * This does a very simple check that the library works.
 */
void
TestCore::testBuzzwords() {
    string bs = Faker::Company::catch_phrase();
    string name = Faker::Company::name();

    CPPUNIT_ASSERT_GREATER_MESSAGE("We expected something useful", 0, static_cast<int>(bs.length()) );
    CPPUNIT_ASSERT_NOT_EQUALS("We got the dummy response", string("This is a dummy catch phrase"), bs);

    CPPUNIT_ASSERT_GREATER_MESSAGE("We expected something useful for the name", 0, static_cast<int>(name.length()) );
}

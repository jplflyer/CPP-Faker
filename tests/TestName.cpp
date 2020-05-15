#include <iostream>
#include <algorithm>

#include <faker/Name.h>

#include "TestName.h"

using std::cout;
using std::endl;
using std::string;

string TEST_NAME = "TestCore";

CPPUNIT_TEST_SUITE_REGISTRATION(TestName);

TestName::TestName()
{
    Faker::Base::setConfigDir("./locales");
}


/**
 * Test that Faker::Name::name() returns something expected.
 *
 * Expected formats (at the time I'm writing this test):
 *
 *		#{prefix} #{first_name} #{last_name}
 *		#{first_name} #{last_name} #{suffix}
 *		#{first_name} #{last_name}
 */
void
TestName::testName()
{
    for (int index = 0; index < 10; ++index) {
        string name = Faker::Name::name();
        int spacesCount = std::count(name.begin(), name.end(), ' ');

        CPPUNIT_ASSERT_GREATER_MESSAGE("Name() value should have length", 0, static_cast<int>(name.length()) );
        CPPUNIT_ASSERT_GREATER_MESSAGE(string("Name() ") + name + ": value should have at least 1 space", 0, spacesCount);
        CPPUNIT_ASSERT_LESS_MESSAGE("Name() value should have at no more than 2 spaces", 3, spacesCount);
    }
}

/**
 * Test against formats:
 *
 *		#{prefix} #{first_name} #{last_name} #{last_name}
 *		#{first_name} #{last_name} #{last_name} #{suffix}
 *		#{first_name} #{last_name} #{last_name}
 */
void
TestName::testNameWithMiddle() {
    for (int index = 0; index < 10; ++index) {
        string name = Faker::Name::name_with_middle();
        int spacesCount = std::count(name.begin(), name.end(), ' ');

        CPPUNIT_ASSERT_GREATER_MESSAGE("Name_with_middle() value should have length", 0, static_cast<int>(name.length()) );
        CPPUNIT_ASSERT_GREATER_MESSAGE(string("Name_with_middle() ") + name + ": value should have at least 2 spaces", 1, spacesCount);
        CPPUNIT_ASSERT_LESS_MESSAGE("Name_with_middle() value should have at no more than 3 spaces", 4, spacesCount);
    }
}

void
TestName::testMaleFirstName() {
    for (int index = 0; index < 10; ++index) {
        string name = Faker::Name::male_first_name();
        int spacesCount = std::count(name.begin(), name.end(), ' ');

        CPPUNIT_ASSERT_GREATER_MESSAGE("male_first_name() value should have length", 0, static_cast<int>(name.length()) );
        CPPUNIT_ASSERT_EQUAL_MESSAGE(string("male_first_name() ") + name + ": value should have no spaces", 0, spacesCount);
    }
}

void
TestName::testFemaleFirstName() {
    for (int index = 0; index < 10; ++index) {
        string name = Faker::Name::female_first_name();
        int spacesCount = std::count(name.begin(), name.end(), ' ');

        CPPUNIT_ASSERT_GREATER_MESSAGE("female_first_name() value should have length", 0, static_cast<int>(name.length()) );
        CPPUNIT_ASSERT_EQUAL_MESSAGE(string("female_first_name() ") + name + ": value should have no spaces", 0, spacesCount);
    }
}

/**
 * The sample data has no St. John type last names.
 */
void
TestName::testLastName() {
    for (int index = 0; index < 10; ++index) {
        string name = Faker::Name::last_name();
        int spacesCount = std::count(name.begin(), name.end(), ' ');

        CPPUNIT_ASSERT_GREATER_MESSAGE("last_name() value should have length", 0, static_cast<int>(name.length()) );
        CPPUNIT_ASSERT_EQUAL_MESSAGE(string("last_name() ") + name + ": value should have no spaces", 0, spacesCount);
    }
}

/**
 * Prefixes are 3 or 4 characters.
 */
void
TestName::testPrefix() {
    for (int index = 0; index < 10; ++index) {
        string name = Faker::Name::prefix();
        int spacesCount = std::count(name.begin(), name.end(), ' ');

        CPPUNIT_ASSERT_GREATER_MESSAGE("prefix() value should have length 3 or 4", 2, static_cast<int>(name.length()) );
        CPPUNIT_ASSERT_LESS_MESSAGE("prefix() value should have length 3 or 4", 5, static_cast<int>(name.length()) );
        CPPUNIT_ASSERT_EQUAL_MESSAGE(string("prefix() ") + name + ": value should have no spaces", 0, spacesCount);
    }
}

/**
 * Prefixes are 1..3 characters.
 */
void
TestName::testSuffix() {
    for (int index = 0; index < 10; ++index) {
        string name = Faker::Name::suffix();
        int spacesCount = std::count(name.begin(), name.end(), ' ');

        CPPUNIT_ASSERT_GREATER_MESSAGE("suffix() value should have length 1..3", 0, static_cast<int>(name.length()) );
        CPPUNIT_ASSERT_LESS_MESSAGE("suffix() value should have length 1..3", 4, static_cast<int>(name.length()) );
        CPPUNIT_ASSERT_EQUAL_MESSAGE(string("suffix() ") + name + ": value should have no spaces", 0, spacesCount);
    }
}

void
TestName::testInitials() {
    for (int index = 0; index < 10; ++index) {
        string name = Faker::Name::initials(4);
        int spacesCount = std::count(name.begin(), name.end(), ' ');

        CPPUNIT_ASSERT_EQUAL_MESSAGE("initials() value should have length 4", 0, static_cast<int>(name.length()) );
        CPPUNIT_ASSERT_EQUAL_MESSAGE(string("initials() ") + name + ": value should have no spaces", 0, spacesCount);
    }
}

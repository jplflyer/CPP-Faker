#include <iostream>
#include <string>

#include <faker/Number.h>

#include "TestNumber.h"

using std::cout;
using std::endl;
using std::string;
using namespace Faker;

string TEST_NAME = "TestNumber";

CPPUNIT_TEST_SUITE_REGISTRATION(TestNumber);

std::string rtrim_trailing_zeroes(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return ch != '0';
    }).base(), s.end());

    return s;
}


TestNumber::TestNumber()
{
    Base::setConfigDir("./locales");
}

/**
 * Make sure we get a number of the appropriate length.
 */
void
TestNumber::testNumber() {
    for (int index = 0; index < 10; ++index) {
        int desiredLength = (index % 8) + 1;
        long value = Number::number(desiredLength);
        string valueS = std::to_string(value);

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrong length (" + valueS + ") of number when converted to string", desiredLength, static_cast<int>(valueS.length()));
    }
}

/**
 * Make sure we get a number of the appropriate length.
 */
void TestNumber::testLeadingZeroNumber() {
    for (int index = 0; index < 10; ++index) {
        int desiredLength = (index % 8) + 1;
        string value = Number::leading_zero_number(desiredLength);

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect leading zero", '0', value.at(0));
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrong length (" + value + ") of number when converted to string", desiredLength, static_cast<int>(value.length()));
    }
}

void TestNumber::testDecimalPart() {
    for (int index = 0; index < 10; ++index) {
        int desiredLength = (index % 4) + 3;
        string value = Number::decimal_part( desiredLength );

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrong length (" + value + ") of number when converted to string", desiredLength, static_cast<int>(value.length()));
    }
}

void TestNumber::testDecimal() {
    for (int index = 0; index < 10; ++index) {
        double value = Number::decimal (6, 4);

        // We have to right-trim off the trailing zeros because to_string pads it out.
        string valueS = rtrim_trailing_zeroes(std::to_string(value));

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrong length (" + valueS + ") of number when converted to string", 11, static_cast<int>(valueS.length()));
    }
}

void TestNumber::testNonZeroDigit() {
    for (int index = 0; index < 10; ++index) {
        int value = Number::non_zero_digit();
        CPPUNIT_ASSERT_MESSAGE("Value should be 1..9", value > 0);
        CPPUNIT_ASSERT_MESSAGE("Value should be 1..9", value <= 9);
    }
}

void TestNumber::testDigit() {
    for (int index = 0; index < 10; ++index) {
        int value = Number::digit();
        CPPUNIT_ASSERT_MESSAGE("Value should be 0..9", value >= 0);
        CPPUNIT_ASSERT_MESSAGE("Value should be 0..9", value <= 9);
    }
}

void TestNumber::testHexadecimal() {
    for (int index = 0; index < 10; ++index) {
        string value = Number::hexadecimal(8);

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrong length (" + value + ") of number when converted to string", 8, static_cast<int>(value.length()));
        CPPUNIT_ASSERT_EQUAL_MESSAGE("String (" + value + ") should contain only hex", string::npos, value.find_first_not_of("0123456789abcdef"));
    }

}

void TestNumber::testNormal() {
}

void TestNumber::testBetween() {
}

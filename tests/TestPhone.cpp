#include <iostream>

#include <faker/PhoneNumber.h>
#include <faker/Data.h>

#include "TestPhone.h"

using std::cout;
using std::endl;
using std::string;
using namespace Faker;

string TEST_NAME = "TestCore";

CPPUNIT_TEST_SUITE_REGISTRATION(TestPhone);

static bool matches(const std::string & format, const std::string & number);

TestPhone::TestPhone()
{
    Faker::Base::setConfigDir("./locales");
}

/**
 * This is a complicated test. Phone numbers are built from this:
 *
 * "formats": [
 *     "###-###-####",
 *     "(###) ###-####",
 *     "1-###-###-####",
 *     "###.###.####",
 *     "###-###-#### x###",
 *     "(###) ###-#### x###",
 *     "1-###-###-#### x###",
 *     "###.###.#### x###",
 *     "###-###-#### x####",
 *     "(###) ###-#### x####",
 *     "1-###-###-#### x####",
 *     "###.###.#### x####",
 *     "###-###-#### x#####",
 *     "(###) ###-#### x#####",
 *     "1-###-###-#### x#####",
 *     "###.###.#### x#####"
 *     ]
 */
void
TestPhone::testPhoneNumber() {
    for (int index = 0; index < 10; ++index) {
        string generatedNumber = PhoneNumber::phone_number();

        // We have to traverse down the path.
        Faker::Data::Pointer enPtr = Data::globalData.find("en");
        CPPUNIT_ASSERT_NOT_NULL("Can't find en", enPtr);

        Faker::Data::Pointer fakerPtr = enPtr->find("faker");
        CPPUNIT_ASSERT_NOT_NULL("Can't find faker", fakerPtr);

        Faker::Data::Pointer phoneNumber = fakerPtr->find("phone_number");
        CPPUNIT_ASSERT_NOT_NULL("Can't find phone_number.formats", phoneNumber);

        Faker::Data::Pointer formats = phoneNumber->find("formats");
        CPPUNIT_ASSERT_NOT_NULL("Can't find phone_number.formats", formats);

        CPPUNIT_ASSERT_EQUAL_MESSAGE("", Data::Type::ARRAY, formats->getType());

        bool matchesOne = false;

        for (Data::Pointer ptr: formats->getArray()) {
            matchesOne = matches(ptr->getString(), generatedNumber);
            if (matchesOne) break;
        }

        CPPUNIT_ASSERT_MESSAGE("Number " + generatedNumber + " does not match any of our formats.", matchesOne);
    }
}

/**
 * Verify this phone number matches this format. Formats are NOT variable-length,
 * so we can do this very simply.
 */
bool matches(const std::string & format, const std::string & number) {
    size_t length = format.length();

    if (number.length() != length) {
        return false;
    }

    for (size_t index = 0; index < length; ++index) {
        char formatChar = format.at(index);
        char phoneChar = number.at(index);

        if (formatChar == '#') {
            if (phoneChar < '0' || phoneChar > '9') {
                return false;
            }
        }
        else if (formatChar != phoneChar) {
            return false;
        }
    }

    return true;
}

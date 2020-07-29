#include <regex>

#include <faker/Address.h>
#include <faker/StringVector.h>

#include "TestAddress.h"

using std::cout;
using std::endl;
using std::string;

string TEST_NAME = "TestAddress";

CPPUNIT_TEST_SUITE_REGISTRATION(TestAddress);

static bool stringContains(const string &str, const string substring) {
    return str.find(substring) != string::npos;
}

/**
 * Tests the simple things. Basically we just call everything and make sure it returns a non-null string.
 */
void TestAddress::testSimple() {
    string rv;

    rv = Faker::Address::city();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected city to be non-empty", string(""), rv);

    rv = Faker::Address::city(true);
    CPPUNIT_ASSERT_MESSAGE("Expected city to include the state", stringContains(rv, ","));

    rv = Faker::Address::street_name();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected street_name to be non-empty", string(""), rv);

    rv = Faker::Address::street_address();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected street_address to be non-empty", string(""), rv);

    rv = Faker::Address::secondary_address();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected secondary_address to be non-empty", string(""), rv);

    rv = Faker::Address::building_number();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected building_number to be non-empty", string(""), rv);

    rv = Faker::Address::community();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected community to be non-empty", string(""), rv);

    rv = Faker::Address::mail_box();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected mail_box to be non-empty", string(""), rv);

    rv = Faker::Address::zip_code();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected zip_code to be non-empty", string(""), rv);

    rv = Faker::Address::time_zone();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected time_zone to be non-empty", string(""), rv);

    rv = Faker::Address::street_suffix();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected street_suffix to be non-empty", string(""), rv);

    rv = Faker::Address::city_suffix();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected city_suffix to be non-empty", string(""), rv);

    rv = Faker::Address::city_prefix();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected city_prefix to be non-empty", string(""), rv);

    rv = Faker::Address::state_abbr();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected state_abbr to be non-empty", string(""), rv);

    rv = Faker::Address::state();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected state to be non-empty", string(""), rv);

    rv = Faker::Address::country();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected country to be non-empty", string(""), rv);

    rv = Faker::Address::country_code();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected country_code to be non-empty", string(""), rv);

    rv = Faker::Address::country_code_long();
    CPPUNIT_ASSERT_NOT_EQUALS("Expected country_code_long to be non-empty", string(""), rv);

}

/**
 * This code tests the full_address() function.
 */
void
TestAddress::testFullAddress() {
    string rv = Faker::Address::full_address();
    CPPUNIT_ASSERT_NOT_EQUALS("Full Address failed. If this test fails, check comments in TestAddress::testFullAddress", string(""), rv);

    //
    // This part tests whether we actually get a zip code. The address will
    // be something like: 5846 Awilda Mall, North Deena, ME 41851-1014.
    // However, this test can fail. The original Ruby files have the zip code
    // portion defined using #{zip_code}, which is great in Ruby, as it will be
    // based off the original object, which has a zip_code function. But C++ doesn't
    // have any form of reflection, and there's no way to do that in a generic fashion.
    // So I haven't coded for it. Instead, I modified the JSON file manually to use
    // #{postal_code} instead, which we can look up inside the JSON file.
    //
    // So if this test fails, it is probably because someone regenerated the JSON
    // files from the original YAML files, and my hand-edit was replaced. The temporary
    // fix is to hand-edit the JSON again.
    //
    // "full_address": [
    //     "#{street_address}, #{city}, #{state_abbr} #{postcode}",
    //     "#{secondary_address} #{street_address}, #{city}, #{state_abbr} #{postcode}"
    // ],
    //
    // It's the postcode part, probably getting set back to zip_code in the two places.
    //
    // A permanent fix is to implment pseudo-reflection in Data::expandString(). We'd
    // have to pass in an Address object and implement a virtual method in Faker::Base
    // to be able to look up methods by string-name of their methods. But I don't
    // feel like doing that right now until it becomes a bigger problem.
    //
    Faker::StringVector sVec;

    sVec.tokenize(rv, " ");
    CPPUNIT_ASSERT_GREATER_MESSAGE("Expect more than 4 parts to an address", 4, static_cast<int>(sVec.size()) );

    string zip = sVec.back();

    //
    // Matches 12345 and 12345-1234
    //
    std::regex rx("\\d{5}(-\\d{4})?");
    CPPUNIT_ASSERT_MESSAGE(
           "Expected zip code portion to look like a zip code: " + zip + ". If this test fails, check comments in TestAddress::testFullAddress",
           regex_match(zip.begin(), zip.end(), rx));
}

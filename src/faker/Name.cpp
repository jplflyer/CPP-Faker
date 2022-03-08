#include "Name.h"

/**
 * Constructor.
 */
Faker::Name::Name()
{
}

/**
 * Produces a random name.
 *
 * ## Examples
 *   Faker::Name.name  => "Tyshawn Johns Sr."
 */
std::string Faker::Name::name() {
    return parse("name.name");
}

/**
 * Produces a random name with middle name.
 *
 * ## Examples
 *   Faker::Name.name_with_middle  => "Aditya Elton Douglas"
 */
std::string Faker::Name::name_with_middle() {
    return parse("name.name_with_middle");
}

/**
 * Produces a random first name.
 *
 * ## Examples
 *   Faker::Name.first_name  => "Kaci"
 */
std::string Faker::Name::first_name() {
    return parse("name.first_name");
}

/**
 * Produces a random male first name.
 *
 * ## Examples
 *   Faker::Name.male_first_name  => "Edward"
 */
std::string Faker::Name::male_first_name() {
    return parse("name.male_first_name");
}

/**
 * Produces a random female first name.
 *
 * ## Examples
 *   Faker::Name.female_first_name  => "Natasha"
 */
std::string Faker::Name::female_first_name() {
    return parse("name.female_first_name");
}

/**
 * Produces a random last name.
 *
 * ## Examples
 *   Faker::Name.last_name  => "Ernser"
 */
std::string Faker::Name::last_name() {
    return parse("name.last_name");
}

/**
 * Produces a random name prefix.
 *
 * ## Examples
 *   Faker::Name.prefix  => "Mr."
 */
std::string Faker::Name::prefix() {
    return parse("name.prefix");
}

/**
 * Produces a random name suffix.
 *
 * ## Examples
 *   Faker::Name.suffix  => "IV"
 */
std::string Faker::Name::suffix() {
    return parse("name.suffix");
}

/**
 * Produces random initials.
 *
 * @param number [Integer] Number of digits that the generated initials should have.
 *
 * ## Examples
 *   Faker::Name.initials()           => "NJM"
 *   Faker::Name.initials(2)          => "NM"
 */
std::string Faker::Name::initials(int number) {
    //(0...number).map { rand(65..90).chr }.join
    std::string retVal = "";
    for (int index = 0; index < number; ++index) {
        char c = 'A' + randomNumber(0, 25);
        retVal += c;
    }
    return retVal;
}

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
 * @return [String]
 *
 * @example
 *   Faker::Name.name  *=> "Tyshawn Johns Sr."
 */
std::string Faker::Name::name() {
    return parse("name.name");
}

/**
 * Produces a random name with middle name.
 *
 * @return [String]
 *
 * @example
 *   Faker::Name.name_with_middle  *=> "Aditya Elton Douglas"
 */
std::string Faker::Name::name_with_middle() {
    return parse("name.name_with_middle");
}

/**
 * Produces a random first name.
 *
 * @return [String]
 *
 * @example
 *   Faker::Name.first_name  *=> "Kaci"
 */
std::string Faker::Name::first_name() {
    return parse("name.first_name");
}

/**
 * Produces a random male first name.
 *
 * @return [String]
 *
 * @example
 *   Faker::Name.male_first_name  *=> "Edward"
 */
std::string Faker::Name::male_first_name() {
    return parse("name.male_first_name");
}

/**
 * Produces a random female first name.
 *
 * @return [String]
 *
 * @example
 *   Faker::Name.female_first_name  *=> "Natasha"
 */
std::string Faker::Name::female_first_name() {
    return parse("name.female_first_name");
}

/**
 * Produces a random last name.
 *
 * @return [String]
 *
 * @example
 *   Faker::Name.last_name  *=> "Ernser"
 */
std::string Faker::Name::last_name() {
    return parse("name.last_name");
}

/**
 * Produces a random name prefix.
 *
 * @return [String]
 *
 * @example
 *   Faker::Name.prefix  *=> "Mr."
 */
std::string Faker::Name::prefix() {
    return parse("name.prefix");
}

/**
 * Produces a random name suffix.
 *
 * @return [String]
 *
 * @example
 *   Faker::Name.suffix  *=> "IV"
 */
std::string Faker::Name::suffix() {
    return parse("name.suffix");
}

/**
 * Produces random initials.
 *
 * @param digits [Integer] Number of digits that the generated initials should have.
 * @return [String]
 *
 * @example
 *   Faker::Name.initials()           *=> "NJM"
 *   Faker::Name.initials(2)          *=> "NM"
 *
 * @faker.version 1.8.5
 */
std::string Faker::Name::initials(int number) {
    //(0...number).map { rand(65..90).chr }.join
    return "";
}

#include <string>
#include <iostream>

#include "Address.h"

using std::string;
using namespace Faker;


/**
 * Produces the name of a city.
 *
 * @param withState Whether to include the state name in the output.
 *
 * ## Examples
 *   Faker::Address.city() => "Imogeneborough"
 *
 *   Faker::Address.city(true) => "Northfort, California"
 */
std::string Faker::Address::city(bool withState) {
    if (withState) {
        return parse("address.city") + ", " + parse("address.state");
    }
    return parse("address.city");
}

/**
 * Produces a street name.
 *
 * ## Examples
 *   Faker::Address.street_name => "Larkin Fork"
 */
std::string Faker::Address::street_name() {
    return parse("address.street_name");
}

/**
 * Produces a street address.
 *
 * @param include_secondary Whether or not to include the secondary address.
 *
 * ## Examples
 *   Faker::Address.street_address => "282 Kevin Brook"
 *
 *   Faker::Address.street_address => "282 Kevin Brook Apt. 3"
 */
std::string Faker::Address::street_address(bool include_secondary) {
    if (!include_secondary) {
        return parse("address.street_address");
    }
    return parse("address.street_address") + " " + secondary_address();
}

/**
 * Produces a secondary address.
 *
 * ## Examples
 *   Faker::Address.secondary_address => "Apt. 672"
 */
std::string Faker::Address::secondary_address() {
    return parse ("address.secondary_address");
}

/**
 * Produces a building number.
 *
 * ## Examples
 *   Faker::Address.building_number => "7304"
 */
std::string Faker::Address::building_number() {
    return parse("address.building_number");
}

/**
 * Produces the name of a community.
 *
 * ## Examples
 *   Faker::Address.community => "University Crossing"
 */
std::string Faker::Address::community() {
    return parse("address.community");
}

/**
 *
 * Produces a mail box number.
 * ## Examples
 *   Faker::Address.mail_box => "PO Box 123"
 */
std::string Faker::Address::mail_box() {
    return parse("address.mail_box");
}

/**
 * Produces a Zip Code.
 *
 * @param state_abbreviation [String] an abbreviation for a state where the zip code should be located.
 *
 * ## Examples
 *   Faker::Address.zip_code => "58517"
 *
 *   Faker::Address.zip_code => "23285-4905"
 *
 *   Faker::Address.zip_code(state_abbreviation: "CO") => "80011"
 */
std::string Faker::Address::zip_code(std::string state_abbreviation) {
    if (state_abbreviation.size() == 0) {
        return parse ("address.postcode");
    }

    return parse("address.postcode_by_state." + state_abbreviation);
}

/**
 * Produces the name of a time zone.
 *
 * ## Examples
 *   Faker::Address.time_zone => "Asia/Yakutsk"
 */
std::string Faker::Address::time_zone() {
    return parse("address.time_zone");
}

/**
 * Produces a street suffix.
 *
 * ## Examples
 *   Faker::Address.street_suffix => "Street"
 */
std::string Faker::Address::street_suffix() {
    return parse ("address.street_suffix");
}

/**
 * Produces a city suffix.
 *
 * ## Examples
 *   Faker::Address.city_suffix => "fort"
 */
std::string Faker::Address::city_suffix() {
    return parse ("address.city_suffix");
}

/**
 * Produces a city prefix.
 *
 * ## Examples
 *   Faker::Address.city_prefix => "Lake"
 */
std::string Faker::Address::city_prefix() {
    return parse ("address.city_prefix");
}

/**
 * Produces a state abbreviation.
 *
 * ## Examples
 *   Faker::Address.state_abbr => "AP"
 */
std::string Faker::Address::state_abbr() {
    return parse ("address.state_abbr");
}

/**
 * Produces the name of a state.
 *
 * ## Examples
 *   Faker::Address.state => "California"
 */
std::string Faker::Address::state() {
    return parse ("address.state");
}

/**
 * Produces the name of a country.
 *
 * ## Examples
 *   Faker::Address.country => "French Guiana"
 */
std::string Faker::Address::country() {
    return parse ("address.country");
}

/**
 * Produces a country by ISO country code. See the
 * [List of ISO 3166 country codes](https://en.wikipedia.org/wiki/List_of_ISO_3166_country_codes)
 * on Wikipedia for a full list.
 *
 * @param code [String] An ISO country code.
 *
 * ## Examples
 *   Faker::Address.country_by_code(code: "NL") => "Netherlands"
 */
std::string Faker::Address::country_by_code(std::string code) {
    return parse ("address.country_by_code." + code);
}

/**
 * Produces an ISO 3166 country code when given a country name.
 *
 * @param name [String] Country name in snake_case format.
 *
 * ## Examples
 *   Faker::Address.country_name_to_code(name: "united_states") => "US"
 */
std::string Faker::Address::country_name_to_code(std::string name) {
    return parse ("address.country_by_name." + name);
}

/**
 * Produces an ISO 3166 country code.
 *
 * ## Examples
 *   Faker::Address.country_code => "IT"
 */
std::string Faker::Address::country_code() {
    return parse ("address.country_code");
}

/**
 * Produces a long (alpha-3) ISO 3166 country code.
 *
 * ## Examples
 *   Faker::Address.country_code_long => "ITA"
 */
std::string Faker::Address::country_code_long() {
    return parse ("address.country_code_long");
}

/**
 * Produces a latitude.
 *
 * ## Examples
 *   Faker::Address.latitude => -58.172562
 */
double Faker::Address::latitude() {
    string degrees = std::to_string(randomNumber(-89, 89)) + "." + randomDigits(6);
    return std::stod(degrees);
}

/**
 * Produces a longitude.
 *
 * ## Examples
 *   Faker::Address.longitude => -156.655483
 */
double Faker::Address::longitude() {
    string degrees = std::to_string(randomNumber(-179, 179)) + "." + randomDigits(6);
    return std::stod(degrees);
}

/**
 * Produces a full address.
 *
 * ## Examples
 *   Faker::Address.full_address
 *     => "282 Kevin Brook, Imogeneborough, CA 58517"
 */
std::string Faker::Address::full_address() {
    return parse("address.full_address");
}

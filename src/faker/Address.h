#pragma once

#include "Base.h"

namespace Faker {
    class Address;
}

class Faker::Address: public Faker::Base
{
public:
    // Produces the name of a city.
    static std::string city(bool withState = false);

    // Produces a street name.
    static std::string street_name();

    // Produces a street address.
    static std::string street_address(bool include_secondary = false);

    // Produces a secondary address.
    static std::string secondary_address();

    // Produces a building number.
    static std::string building_number();

    // Produces the name of a community.
    static std::string community();

    // Produces a mail box number.
    static std::string mail_box();

    // Produces a Zip Code.
    static std::string zip_code(const std::string state_abbreviation = "");

    // Produces the name of a time zone.
    static std::string time_zone();

    static std::string zip(const std::string state_abbreviation = "") { return zip_code(state_abbreviation); }
    static std::string postcode(const std::string state_abbreviation = "") { return zip_code(state_abbreviation); }

    // Produces a street suffix.
    static std::string street_suffix();

    // Produces a city suffix.
    static std::string city_suffix();

    // Produces a city prefix.
    static std::string city_prefix();

    // Produces a state abbreviation.
    static std::string state_abbr();

    // Produces the name of a state.
    static std::string state();

    // Produces the name of a country.
    static std::string country();

    // Produces a country by ISO country code. See the
    static std::string country_by_code(std::string code = "US");

    // Produces an ISO 3166 country code when given a country name.
    static std::string country_name_to_code(std::string name = "united_states");

    // Produces an ISO 3166 country code.
    static std::string country_code();

    // Produces a long (alpha-3) ISO 3166 country code.
    static std::string country_code_long();

    // Produces a latitude.
    static double latitude();

    // Produces a longitude.
    static double longitude();

    // Produces a full address.
    static std::string full_address();
};

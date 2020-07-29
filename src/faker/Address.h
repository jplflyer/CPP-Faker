#pragma once

#include "Base.h"

namespace Faker {
    class Address;
}

/**
 * Handling street addresses.
 */
class Faker::Address: public Faker::Base
{
public:
    static std::string city(bool withState = false);

    static std::string street_name();


    static std::string street_address(bool include_secondary = false);

    static std::string secondary_address();

    static std::string building_number();

    static std::string community();

    static std::string mail_box();

    static std::string zip_code(const std::string state_abbreviation = "");

    static std::string time_zone();

    static std::string zip(const std::string state_abbreviation = "") { return zip_code(state_abbreviation); }
    static std::string postcode(const std::string state_abbreviation = "") { return zip_code(state_abbreviation); }

    static std::string street_suffix();

    static std::string city_suffix();

    static std::string city_prefix();

    static std::string state_abbr();

    static std::string state();

    static std::string country();

    static std::string country_by_code(std::string code = "US");

    static std::string country_name_to_code(std::string name = "united_states");

    static std::string country_code();

    static std::string country_code_long();

    static double latitude();

    static double longitude();

    static std::string full_address();
};

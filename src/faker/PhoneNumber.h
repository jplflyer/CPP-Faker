#pragma once

#include "Base.h"

namespace Faker {
    class PhoneNumber;
}

class Faker::PhoneNumber : public Faker::Base
{
public:
    PhoneNumber();

    static std::string phone_number();
    static std::string cell_phone();
    static std::string country_code();
    static std::string phone_number_with_country_code();
    static std::string cell_phone_with_country_code();
    /* static std::string cell_phone_in_e164(); */

    // US and Canada only
    static std::string area_code();

    // US and Canada only
    static std::string exchange_code();

    // US and Canada only
    // Can be used for both extensions and last four digits of phone number.
    // Since extensions can be of variable length, this method taks a length parameter
    static std::string subscriber_number(int length = 4);

    static std::string extension(int length = 4) { return subscriber_number(length); }

};

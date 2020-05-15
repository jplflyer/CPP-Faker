#include "PhoneNumber.h"

using namespace Faker;

/**
 * Constructor.
 */
Faker::PhoneNumber::PhoneNumber()
{
}

std::string Faker::PhoneNumber:: phone_number() {
    return parse("phone_number.formats");
}

std::string Faker::PhoneNumber:: cell_phone() {
    return parse("cell_phone.formats");
}

std::string Faker::PhoneNumber:: country_code() {
    return std::string("+") + parse("country_code");
}

std::string Faker::PhoneNumber:: phone_number_with_country_code() {
    return country_code() + " " + phone_number();
}

std::string Faker::PhoneNumber:: cell_phone_with_country_code() {
    return country_code() + " " + cell_phone();
}

/*
 I don't know what this is supposed to be.
std::string Faker::PhoneNumber:: cell_phone_in_e164() {
    return cell_phone_with_country_code.delete("^+0-9")
}
*/

// US and Canada only
std::string Faker::PhoneNumber:: area_code() {
    return parse("phone_number.area_code");
}

// US and Canada only
std::string Faker::PhoneNumber:: exchange_code() {
    return parse("phone_number.exchange_code");
}

// US and Canada only
// Can be used for both extensions and last four digits of phone number.
// Since extensions can be of variable length, this method takes a length parameter
std::string Faker::PhoneNumber:: subscriber_number(int length) {
    return randomDigits(length);
}


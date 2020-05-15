#pragma once

#include "Base.h"

namespace Faker {
    class Number;
} // namespace Faker

class Faker::Number : public Faker::Base
{
public:
    Number();

    static long			number( int digits = 10);
    static std::string	leading_zero_number( int digits = 10);
    static std::string	decimal_part( int digits = 10);
    static double		decimal( int l_digits = 5, int r_digits = 2);
    static long			non_zero_digit();
    static long			digit();
    static std::string	hexadecimal( int digits = 6);
    static double		normal(  double = 1.0, double standard_deviation = 1.0);
    static long			between( long from = 1, long to = 5000);
};

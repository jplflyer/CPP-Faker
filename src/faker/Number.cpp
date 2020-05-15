#include <cmath>

#include "Number.h"

using namespace Faker;
using std::string;

static char intToHex(int value) {
    if (value >= 16) {
        // Naughty.
        return '0';
    }

    if (value < 10) {
        return '0' + value;
    }
    return 'a' + (value - 10);
}

/**
 * Constructor.
 */
Faker::Number::Number() {
}

/**
 * Produce a random number.
 *
 * @param digits [Integer] Number of digits that the generated number should have.
 * @return [Integer]
 *
 * @example
 *   Faker::Number.number(digits: 10)  *=> 1968353479
 */
long Faker::Number::number(int digits) {
    long retVal = Base::randomNumber(1, 9);

    for (int index = 1; index < digits; ++index) {
        retVal = retVal * 10 + Base::randomNumber(0, 9);
    }

    return retVal;
}

/**
 * Produce a random number with a leading zero.
 *
 * @param digits [Integer] Number of digits that the generated number should have.
 * @return [String]
 *
 * @example
 *   Faker::Number.leading_zero_number(digits: 10)  *=> "0669336915"
 */
string Faker::Number::leading_zero_number(int digits) {
    string retVal = string("0");

    if (digits > 1) {
        retVal += Base::randomDigits(digits - 1);
    }

    return retVal;
}

/**
 * Produce a number with a number of digits, preserves leading zeroes.
 * This might be used as the the milliseconds portion of seconds.milliseconds,
 * which would need to be zero-filled.
 *
 * @param digits [Integer] Number of digits that the generated number should have.
 * @return [String]
 *
 * @example
 *   Faker::Number.decimal_part(digits: 2)  *=> "09"
 *
 * @faker.version 1.0.0
 */
string Faker::Number::decimal_part(int digits) {
    string retVal = Base::randomDigits(digits);

    while (static_cast<int>(retVal.length()) < digits) {
        retVal = "0" + retVal;
    }

    return retVal;
}

/**
 * Produces a float. This method will not start or end with zero so that
 * it prints to the full expected size. You won't get 0.00.
 *
 * @param l_digits [Integer] Number of digits that the generated decimal should have to the left of the decimal point.
 * @param r_digits [Integer] Number of digits that the generated decimal should have to the right of the decimal point.
 * @return [Float]
 *
 * @example
 *   Faker::Number.decimal(l_digits: 2)  *=> 11.88
 *   Faker::Number.decimal(l_digits: 3, r_digits: 3)  *=> 181.843
 *
 * @faker.version 1.0.0
 */
double Faker::Number::decimal(  int l_digits, int r_digits ) {
    double retVal = Base::randomNumber(1, 9);	// Start with non-zero.
    double multiplier = 0.1;

    // Already have 1 digit.
    for (int index = 1; index < l_digits; ++index) {
        retVal = retVal * 10 + Base::randomNumber(0, 9);
    }

    // Start this at one to force a non-zero as the last value in order
    // to get the full number of digits.
    for (int index = 1; index < r_digits; ++index) {
        retVal += multiplier * static_cast<double>(Base::randomNumber(0, 9));
        multiplier = multiplier / 10;
    }
    retVal += multiplier * static_cast<double>(Base::randomNumber(1, 9));

    return retVal;
}

/**
 * Produces a non-zero single-digit integer.
 *
 * @return [Integer]
 *
 * @example
 *   Faker::Number.non_zero_digit  *=> 8
 */
long Faker::Number::non_zero_digit() {
    return Base::randomNumber(1, 9);
}

/**
 * Produces a single-digit integer.
 *
 * @return [Integer]
 *
 * @example
 *   Faker::Number.digit  *=> 1
 */
long Faker::Number::digit() {
    return Base::randomNumber(0, 9);
}

/**
 * Produces a number in hexadecimal format.
 *
 * @param digits [Integer] Number of digits in the he
 * @return [String]
 *
 * @example
 *   Faker::Number.hexadecimal(digits: 3)  *=> "e74"
 */
string Faker::Number::hexadecimal( int digits ) {
    string retVal = string("") + intToHex(Base::randomNumber(1, 15));

    for (int index = 1; index < digits; ++index) {
        retVal += intToHex(Base::randomNumber(0, 15));
    }
    return retVal;
}

/**
 * Produces a float given a mean and standard deviation.
 *
 * @param mean [Integer]
 * @param standard_deviation [Integer, Float]
 * @return [Float]
 *
 * @example
 *   Faker::Number.normal(mean: 50, standard_deviation: 3.5)  *=> 47.14669604069156
 */
double Faker::Number::normal( double mean, double standard_deviation) {
    // The Rails "rand" method produces numbers in the range 0..1.
    //
    // The original Ruby code was:
    //
    // theta = 2 * Math::PI * rand
    // rho = Math.sqrt(-2 * Math.log(1 - rand))
    // scale = standard_deviation * rho
    // mean + scale * Math.cos(theta)
    //
    // So theta ranges evenly from 0 to 2*PI.
    // For calculating rho, we're using Math.log(0..1), all of which
    // are negative, so rho ranges from 0..sqrt(2).

    double firstRand = static_cast<double>( Base::randomNumber(0, 99999)) / 100000.0;	// Never reach 1
    double secondRand = static_cast<double>(Base::randomNumber(0, 99999)) / 100000.0;	// Never reach 1

    double theta = 2.0 * M_PI * firstRand;

    double rho = std::sqrt( -2.0 * std::log(1.0 - secondRand) );
    double scale = standard_deviation * rho;

    return mean + scale * std::cos(theta);
}

/**
 * Produces a number between two provided values. Boundaries are inclusive.
 *
 * @param from [Integer] The lowest number to include.
 * @param to [Integer] The highest number to include.
 * @return [Integer]
 *
 * @example
 *   Faker::Number.between(from: 1, to: 10)  *=> 7
 */
long Faker::Number::between( long from, long to ) {
    return Base::randomNumber(from, to);
}

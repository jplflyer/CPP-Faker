#include "Company.h"

using std::cout;
using std::endl;
using std::string;
using namespace Faker;

/**
 * Produces a company name.
 *
 * @return [String]
 *
 * @example
 *   Faker::Company.name #=> "Roberts Inc"
 *
 */
std::string Faker::Company::name() {
    return parse("company.name");
}

/**
 * Produces a company suffix.
 *
 * @return [String]
 *
 * @example
 *   Faker::Company.suffix #=> "LLC"
 */
std::string Faker::Company::suffix() {
    return parse("company.suffix");
}

/**
 * Produces a company industry.
 *
 * @return [String]
 *
 * @example
 *   Faker::Company.industry #=> "Food & Beverages"
 */
std::string Faker::Company::industry() {
    return parse("company.industry");
}

/**
 * Produces a company catch phrase.
 *
 * @return [String]
 *
 * @example
 *   Faker::Company.catch_phrase #=> "Grass-roots grid-enabled portal"
 */
std::string Faker::Company::catch_phrase() {
    //         translate('faker.company.buzzwords').collect { |list| sample(list) }.join(' ')
    //
    // company.buzzwords is an array of a string-array. I think this grabs one random
    // string from each of the three arrays. We'll do that ourself.

    Data::Vector dataStack;
    Data::Pointer buzzwords = find("company.buzzwords", dataStack);

    if (buzzwords == nullptr) {
        return "This is a dummy catch phrase";
    }

    string retVal;
    string delim = "";
    if (buzzwords->getType() == Data::Type::ARRAY) {
        for (Data::Pointer ptr: buzzwords->getArray()) {
            Data::Vector wordsArray = ptr->getArray();
            size_t index = Base::randomNumber(0, wordsArray.size());
            if (index < wordsArray.size()) {
                retVal += delim + wordsArray.at(index)->getString();
                delim = " ";
            }
        }
    }

    return retVal;
}

/**
 * Produces a company buzzword.
 *
 * @return [String]
 *
 * @example
 *   Faker::Company.buzzword #=> "flexibility"
 */
std::string Faker::Company::buzzword() {
    return "";
}

/**
 * Produces some company BS.
 *
 * @return [String]
 *
 * @example
 *   Faker::Company.bs #=> "empower customized functionalities"
 *
 * When a straight answer won't do, BS to the rescue!
 */
std::string Faker::Company::bs() {
    return "";
}

/**
 * Produces a company EIN (Employer Identification Number).
 *
 * @return [String]
 *
 * @example
 *   Faker::Company.ein #=> "07-4009024"
 */
std::string Faker::Company::ein() {
    return Base::randomDigits(2) + "-" + Base::randomDigits(7);
}

/**
 * Produces a company duns number.
 *
 * @return [String]
 *
 * @example
 *   Faker::Company.duns_number #=> "70-655-5105"
 */
std::string Faker::Company::duns_number() {
    return Base::randomDigits(2) + "-" + Base::randomDigits(3) + "-" + Base::randomDigits(4);
}

/**
 * Produces a company logo.
 *
 * @return [String]
 *
 * @example
 *   Faker::Company.logo #=> "https://pigment.github.io/fake-logos/logos/medium/color/12.png"
 */
std::string Faker::Company::logo() {
    int randomNumber = Base::randomNumber(1, 13);
    return std::string("https://pigment.github.io/fake-logos/logos/medium/color/") + std::to_string(randomNumber) + ".png";
}

/**
 * Produces a company type.
 *
 * @return [String]
 *
 * @example
 *   Faker::Company.type #=> "Partnership"
 */
std::string Faker::Company::type() {
    return parse("company.type");
}

/**
 * Produces a company profession.
 *
 * @return [String]
 *
 * @example
 *   Faker::Company.profession #=> "factory worker"
 */
std::string Faker::Company::profession() {
    return parse("company.profession");
}

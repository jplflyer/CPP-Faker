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
    Data::Vector dataStack;
    Data::Pointer bs = find("company.buzzwords", dataStack);
    string retVal = "";

    if (bs != nullptr) {
        retVal = selectRandomWords(bs);
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
    Data::Vector dataStack;
    Data::Pointer buzzwords = find("company.buzzwords", dataStack);
    string retVal = "";

    if (buzzwords != nullptr) {
        retVal = selectOneRandomWord(buzzwords);
    }

    return retVal;
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
    Data::Vector dataStack;
    Data::Pointer bs = find("company.bs", dataStack);
    string retVal = "";

    if (bs != nullptr) {
        retVal = selectRandomWords(bs);
    }

    return retVal;
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

/**
 * this is a helper method for selecting either one word or a series of space-delimeted words.
 *
 * The path given will feed us (probably) to an array of an array of strings. We'll traverse down
 * from there until we get to the bottom and then randomly select one word from each array.
 */
std::string Faker::Company::selectRandomWords(Data::Pointer top) {
    string retVal = "";

    // This should always be the case, but in case we're used for data I haven't anticipated.
    if (top->getType() == Data::Type::ARRAY) {
        Data::Vector & vec = top->getArray();

        // I don't expect empty arrays.
        // We should be one of two cases. Either we're nested, and we have to dive down
        // (recursively), or we're pointing to an array of strings, and we randomly pick
        // one string.

        if (vec.size() > 0) {
            Data::Pointer first = vec.at(0);

            // We're an array of strings, so just poick one randomly?
            if (first->getType() == Data::Type::STRING) {
                // We're an array of strings, so randomly pick one and return.
                Data::Pointer ptr = top->selectFromArray();
                retVal = ptr->getString();
            }

            // We're an array of arrays, and have to recurse, once per child array.
            else {
                string delim = "";
                for (Data::Pointer ptr: vec) {
                    retVal += delim + selectRandomWords(ptr);
                    delim = " ";
                }
            }
        }
    }

    else if (top->getType() == Data::Type::STRING) {
        retVal = top->getString();
    }

    return retVal;
}

/**
 * This method is very similar to selectRandomWords(), but we randomly select just ONE.
 */
std::string
Faker::Company::selectOneRandomWord(Data::Pointer top) {
    string retVal = "";

    // This is what happens when we get to the bottom.
    if (top->getType() == Data::Type::STRING) {
        retVal = top->getString();
    }

    // This is the path as we're getting to the bottom.
    else if (top->getType() == Data::Type::ARRAY) {
        retVal = selectOneRandomWord(top->selectFromArray());
    }


    return retVal;
}


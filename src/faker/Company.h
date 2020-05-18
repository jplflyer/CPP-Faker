#pragma once

#include "Base.h"

namespace Faker {
    class Company;
}

class Faker::Company : public Faker::Base
{
public:
    static std::string name();
    static std::string suffix();
    static std::string industry();
    static std::string catch_phrase();
    static std::string buzzword();
    static std::string bs();
    static std::string ein();
    static std::string duns_number();
    static std::string logo();
    static std::string type();
    static std::string profession();
};

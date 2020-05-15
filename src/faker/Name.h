#pragma once

#include <string>
#include "Base.h"

namespace Faker {
    class Name;
}

class Faker::Name: public Faker::Base
{
public:
    Name();

    static std::string name();

    static std::string name_with_middle();

    static std::string first_name();

    static std::string male_first_name();
    static std::string first_name_men() { return male_first_name(); }
    static std::string masculine_name() { return male_first_name(); }

    static std::string female_first_name();
    static std::string first_name_women() { return female_first_name(); }
    static std::string feminine_name() { return female_first_name(); }

    static std::string last_name();
    static std::string middle_name() { return last_name(); }

    static std::string prefix();

    static std::string suffix();

    static std::string initials(int number = 3);
};

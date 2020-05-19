#pragma once

#include <string>

#include "Base.h"

namespace Faker {
    class ESports;
} // namespace Faker

class Faker::ESports : public Faker::Base
{
public:
    static std::string player();
    static std::string team();
    static std::string league();
    static std::string event();
    static std::string game();
};

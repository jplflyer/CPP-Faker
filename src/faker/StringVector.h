#pragma once

#include <vector>
#include <string>

namespace Faker {
    class StringVector;
}

class Faker::StringVector: public std::vector<std::string>
{
public:
    StringVector();

    void tokenize(const std::string &, const std::string &);
};

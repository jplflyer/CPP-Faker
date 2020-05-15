CPP-Faker is a (partial) C++ translation of the faker-ruby gem, that is, a library for producing fake data useful in automated testing.

# Build Targets

    make clean
    make [all]
    make docs
    sudo make install

# Usage

    #include <faker/Name.h>
    ...
    std::string fullName = Faker::Name::name();

When building, include -lfaker.

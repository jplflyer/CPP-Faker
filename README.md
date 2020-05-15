# Overview
This is my version of a C++ library for producing fake/mock data for program testing. It is influenced by and uses configuration files from the Ruby Faker library found at https://github.com/faker-ruby/faker. No code was used from that library, but I did translate from some of their YAML data files. As such, I have included a copy of the Faker license.

# License
The software is licensed under the MIT open source license, a copy of which appears in License.txt.

This project was patterened after faker-ruby, and it directly includes (translated) data files from that project. Their license appears in License-faker-ruby.

I have also included json.hpp from https://github.com/nlohmann/json. This software is also licensed under the MIT license.

# Status
As of May, 2020, I have only implemented as much as I need for my own purposes. In this case, that means Name and PhoneNumber. Address might exist soon, as might a few other objects.

The generic code can handle those format strings that I've tested against, but it is every bit possible there are strings buried in all that JSON (from the Faker-Ruby YAML files) that I didn't notice and didn't test against.

# Installation
Requirements:

* boost
* gnu make
* doxygen if you want documentation
* cppunit if you want to run the unit tests

    make
    make docs
    sudo make install

This makes the library and documentation then copies:

* library to /usr/local/lib
* includes to /usr/local/include/faker
* doxygen-produced files to /usr/local/faker/docs
* the JSON locale files to /usr/local/faker/locales

I don't know what will happen on Windows. The code doesn't care where it's installed, but it must be able to find the locale files at runtime. The default is as shown, but you can:

    Faker::Base::setConfigDir("/some-path/locales");

# Usage

Your Code:

    #include <faker/Name.h>
    ...
    std::string name = Faker::Name::name();

# Contributing
If you want to contribute to this project, anything goes, but what we need the most:

* More of the classes implemented. Maybe someone will write a script that takes all the Ruby implementations and translates them into C++.
* Identify any translation strings I'm not handling.
* Someone to test on Windows and possibly produce a better build system.
* Someone to test locales. I did a hack of it. See Faker::Data::setup().
* Improve the documentation.

Feel free to fork and then submit pull requests.

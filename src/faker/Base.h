#pragma once

#include <string>
#include <mutex>
#include <random>

#include "Data.h"

namespace Faker {
    class Base;
}

/**
 * Base class for all other Faker classes.
 */
class Faker::Base {
public:
    static void setConfigDir(const std::string &value) { configDirName = value; }
    static const std::string & getConfigDirName() { return configDirName; }
    static void seed(unsigned long val);
    static void setVerbose(bool value) { verbose = value; }

    static long randomNumber(long low, long high);
    static std::string randomPassword(int length = 8);
    static std::string randomDigits(int length = 1);

    static Data::Pointer find(const std::string &, Data::Vector &, const std::string &beginningLocale = "", const std::string &domain = "faker");
    static std::string parse(const std::string &, const std::string &beginningLocale = "", const std::string &domain = "faker");

protected:
    static void setup();

    static std::string	configDirName;
    static std::string	locale;
    static std::string	localeBase;
    static std::mutex	baseMutex;
    static std::mt19937 randomGenerator;
    static bool			haveBeenSetup;
    static bool			haveBeenSeeded;
    static bool         verbose;
};

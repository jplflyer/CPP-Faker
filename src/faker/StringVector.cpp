#include <string.h>
#include <string>

#include "StringVector.h"

using std::string;

/**
 * Constructor.
 */
Faker::StringVector::StringVector() {
}

/**
 * Populate ourself by splitting this string at any of these delimiters.
 * This is NOT based on a regular expression.
 */
void
Faker::StringVector::tokenize(const string &str, const string &splitter) {
    // We dup it because we're going to be inserting nulls.
    char * dup = strdup(str.c_str());
    char * dupPtr = dup;
    char * context = nullptr;
    char * ptr;

    while ((ptr = strtok_r(dupPtr, splitter.c_str(), &context)) != nullptr) {
        dupPtr = nullptr;	// For subsequent calls

        push_back(ptr);
    }

    // Free our duplicate copy.
    free(dup);
}

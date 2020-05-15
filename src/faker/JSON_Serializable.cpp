#include <iostream>
#include <sstream>

#include <date/date.h>

#include "JSON_Serializable.h"

using namespace std;
using JSON = nlohmann::json;

/**
 * Constructor.
 */
Faker::JSON_Serializable::JSON_Serializable() {
}

/**
 * Destructor.
 */
Faker::JSON_Serializable::~JSON_Serializable() {
}

/**
 * Convert the object to a string.
 */
std::string
Faker::JSON_Serializable::toString() const {
    JSON json;
    toJSON(json);
    return json.dump(2);
}

/**
 * Get this key's value as a string.
 *
 * @returns The object in string representation or an empty string if the key isn't found.
 */
std::string
Faker::JSON_Serializable::stringValue(const JSON &propertyTree, const std::string &key)
{
	auto it = propertyTree.find(key);
	if (it != propertyTree.end()) {
        JSON value = *it;
		if (!value.is_null()) {
			return value.get<string>();
		}
	}
	return "";
}

/**
 * Get this key's value as an int. May throw an exception if the key is found but
 * it's a non-integer value.
 *
 * @returns the value or 0 if not found.
 */
int
Faker::JSON_Serializable::intValue(const JSON &propertyTree, const std::string &key)
{
	auto it = propertyTree.find(key);
	if (it != propertyTree.end()) {
        JSON value = *it;
		if (!value.is_null()) {
			return value.get<int>();
		}
	}
	return 0;
}

/**
 * Get this key's value as a double. May throw an exception if the key is found but
 * it's a non-floating value.
 *
 * @returns the value or 0.0 if not found.
 */
double
Faker::JSON_Serializable::doubleValue(const JSON &propertyTree, const std::string &key)
{
	auto it = propertyTree.find(key);
	if (it != propertyTree.end()) {
        JSON value = *it;
		if (!value.is_null()) {
			return value.get<double>();
		}
	}
    return 0.0;
}

/**
 * Get this key's value as a long. May throw an exception if the key is found but
 * it's a non-numeric value.
 *
 * @returns the value or 0 if not found.
 */
long
Faker::JSON_Serializable::longValue(const JSON &propertyTree, const std::string &key)
{
	auto it = propertyTree.find(key);
	if (it != propertyTree.end()) {
        JSON value = *it;
		if (!value.is_null()) {
			return value.get<long>();
		}
	}
	return 0;
}

/**
 * Get this key's value as a boolean. May throw an exception if the key is found but
 * it's a non-boolean value.
 *
 * @returns the value or false if not found.
 */
bool
Faker::JSON_Serializable::boolValue(const JSON &propertyTree, const std::string &key)
{
	auto it = propertyTree.find(key);
	if (it != propertyTree.end()) {
        JSON value = *it;
		if (!value.is_null()) {
			return value.get<bool>();
		}
	}
	return false;
}

/**
 * Find this key and return the corresponding JSON object.
 *
 * @returns the value or an empty JSON object.
 */
JSON
Faker::JSON_Serializable::jsonValue(const JSON &propertyTree, const std::string &key) {
	auto it = propertyTree.find(key);
	if (it != propertyTree.end()) {
		return *it;
	}
    return JSON::object();
}

/**
 * Returns this key's value as a time_point from the string representation.
 */
chrono::system_clock::time_point
Faker::JSON_Serializable::timeValue(const JSON &propertyTree, const std::string &key)
{
	chrono::system_clock::time_point retVal;
	string strValue = stringValue(propertyTree, key);
	if (strValue.length() > 0) {
		istringstream in{strValue};
		in >> date::parse("%Y-%m-%d %H:%M:%S", retVal);
	}
	return retVal;
}

/**
 * Returns this key's value as a time_point from the string representation.
 */
chrono::system_clock::time_point
Faker::JSON_Serializable::timeValueT(const JSON &propertyTree, const std::string &key)
{
    chrono::system_clock::time_point retVal;
    string strValue = stringValue(propertyTree, key);
    if (strValue.length() > 0) {
        istringstream in{strValue};
        in >> date::parse("%Y-%m-%dT%H:%M:%S", retVal);
    }
    return retVal;
}

/**
 * Use when we're returning an array of ints.
 */
void
Faker::JSON_Serializable::intVectorValue(const JSON &propertyTree, const std::string &key, std::vector<int> &retVal) {
    JSON array = jsonValue(propertyTree, key);

    retVal.clear();

    if (array.is_array()) {
        for (JSON::iterator it = array.begin(); it != array.end(); ++it) {
            JSON value = *it;
            if (value.is_number()) {
                int valueI = value.get<int>();
                retVal.push_back(valueI);
            }
            else if (value.is_string()) {
                retVal.push_back( std::stoi(value.get<string>()) );
            }
        }
    }
}


/**
 * Sets a string value in this JSON only if we have content.
 */
void
Faker::JSON_Serializable::setStringValue(JSON &obj, const std::string &key, const std::string &value) {
    if (key.length() > 0 && value.length() > 0) {
        obj[key] = value;
    }
}

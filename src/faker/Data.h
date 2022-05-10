#pragma once

//
// Our JSON files are a direct translation from faker-ruby's YAML files. They provide structure like:
//
//		en.faker.name.foo
//
// The foos can be:
//
//		A simple string
//		An array of strings
//		A map of string_key:string_value
//		A nested level (OBJECT_MAP)
//
// In the case of name, the structure is:
//
//		en
//			.faker
//				.name
//					.male_first_name		-- an array of simple strings
//					.female_first_nam		-- an array of simple stringse
//					.last_name				-- an array of simple strings
//					.suffix					-- an array of simple strings
//					.prefix					-- an array of simple strings
//					.first_name				-- an array of strings:     "#{female_first_name}", "#{male_first_name}"
//					.name_with_middle		-- an array of strings with choices similar to first_name
//					.name					-- an array of strings with choices similar to first_name
//
// So this is represented by:
//		globalData: OBJECT_MAP [
//			faker: OBJECT_MAP [
//				name: OBJECT_MAP [
//					male_first_name: STRING_ARRAY
//					... all are STRING_ARRAY
//				]
//			]
//		]
//

#include <string>
#include <vector>
#include <map>

#include <faker/JSON_Serializable.h>

namespace Faker {
    class Data;
}

/**
 * Handles the hard part of parsing our JSON files and returning useful information.
 */
class Faker::Data: public Faker::JSON_Serializable {
public:
    enum class Type { UNKNOWN, STRING, OBJECT, ARRAY};

    typedef std::shared_ptr<Faker::Data> Pointer;
    typedef Faker::JSON_Serializable_Vector<Faker::Data> Vector;
    typedef std::map<std::string, Pointer> ObjectMap;
    typedef std::map<std::string, std::string> StringMap;

private:
    /** Our type. */
    Type type = Type::UNKNOWN;

    /** Who we are. */
    std::string ourKey;

    /** Where we came from. */
    std::string ourDirectory;

    /** type == STRING */
    std::string strValue;

    /** type == ARRAY */
    Vector array;

    /** type == OBJECT */
    ObjectMap map;

    static bool verbose;

    void loadFile(const std::string &fileName);

    std::string expandString(Vector &dataStack) const;
    std::string expandFormatString(Vector &dataStack) const;
    std::string expandArray(Vector &dataStack) const;
    std::string expandObject(Vector &dataStack) const;

public:
    Data(Type _type = Type::UNKNOWN);
    virtual ~Data();

    Type getType() const { return type; }

    static bool getVerbose() { return verbose; }
    static void setVerbose(bool value) { verbose = value; }
    Vector & getArray() { return array; }
    const std::string & getString() const { return strValue; }

    void dumpTree(int depth, const std::string &prefix = "") const;

    Data::Pointer find(const std::string &key) const;
    Data::Pointer makeDomain(const std::string &key);
    Data::Pointer load(const std::string &path, const std::string &key);

    /** Implement this method to populate ourself from this json. */
    void fromJSON(const nlohmann::json & json);

    /** Implement this method to populate this json from ourself. */
    void toJSON(nlohmann::json & json) const;

    const std::string & getDirectory() const { return ourDirectory; }

    std::string expand(Vector &dataStack) const;
    Pointer selectFromArray() const;

    static Faker::Data globalData;
};

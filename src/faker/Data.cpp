#include <boost/filesystem.hpp>

#include "Base.h"
#include "Data.h"

using std::cout;
using std::endl;
using std::string;
using namespace Faker;

//======================================================================
// Forward declarations.
//======================================================================
static std::string readFileContents(const std::string& path);

//======================================================================
// Static variables.
//======================================================================
Data Data::globalData(Data::Type::OBJECT);

//======================================================================
// The Class.
//======================================================================
/**
 * Constructor.
 */
Data::Data(Type _type)
    : type(_type)
{
}

/**
 * Destructor.
 */
Data::~Data() {
}

/**
 * A non-destructive load from JSON.
 */
void
Data::fromJSON(const JSON & json) {
    if (json.is_null()) {
        cout << "We're null." << endl;
    }

    else if (json.is_boolean()) {
        cout << "We're just a bool." << endl;
    }

    else if (json.is_number()) {
        cout << "We're just a number." << endl;
    }

    // If an object, we might contain all strings or else more complicated data.
    else if (json.is_object()) {
        type = Type::OBJECT;
        for (auto & it: json.items()) {
            string key = it.key();
            JSON value = it.value();
            Data::Pointer child = find(key);
            if (child == nullptr) {
                child = std::make_shared<Data>();
                child->ourKey = key;
                map.insert(std::pair<string,Pointer>(key, child));
            }
            child->fromJSON(value);
        }
    }

    // If an array, we currently only handle string arrays.
    else if (json.is_array()) {
        type = Type::ARRAY;
        for (JSON::const_iterator it = json.begin(); it != json.end(); ++it) {
            JSON value = *it;
            Pointer child = std::make_shared<Data>();
            array.push_back(child);
            child->fromJSON(value);
        }
    }

    else if (json.is_string()) {
        type = Type::STRING;
        strValue = json.get<string>();
    }
}

/**
 * Output to JSON.
 */
void Data::toJSON(JSON & ) const {}

/**
 * Search ourself for this key.
 */
Data::Pointer
Data::find(const string &key) const {
    if (verbose) {
        cout << ourKey << ": Look for child: " << key << endl;
    }
    Data::Pointer retVal = nullptr;

    if (type == Type::OBJECT) {
        auto ptr = map.find(key);
        if (ptr != map.end()) {
            retVal = ptr->second;
        }
    }
    else if (type == Type::UNKNOWN) {
        if (verbose) {
            cout << ourKey << ": we don't know what we are." << endl;
        }
    }
    else if (type == Type::STRING) {
        if (verbose) {
            cout << ourKey << ": find() on type string." << endl;
        }
    }
    else if (type == Type::ARRAY) {
        if (verbose) {
            cout << ourKey << ": find() on type array: " << key << endl;
        }
    }

    return retVal;
}

/**
 * Load a subkey.
 */
Data::Pointer
Data::load(const string &path, const string &key) {
    Data::Pointer retVal = nullptr;

    string tryFile = path + "/" + key + ".json";
    if (boost::filesystem::exists(tryFile)) {
        loadFile(tryFile);
    }

    return retVal;
}

Data::Pointer
Data::makeDomain(const string &key) {
    Data::Pointer retVal = std::make_shared<Data>(Type::OBJECT);
    retVal->ourKey = key;
    retVal->ourDirectory = ourDirectory;
    map.insert( std::pair<string, Pointer>(key, retVal) );

    return retVal;
}

/**
 * Load ourself from this file.
 */
void
Data::loadFile(const string &fileName) {
    string contents = readFileContents(fileName);
    JSON json = JSON::parse(contents);
    fromJSON(json);
}

/**
 * Dump ourself to a certain depth.
 */
void
Data::dumpTree(int depth, const string & prefix) const {
    switch (type) {
        case Type::UNKNOWN: cout << prefix << "Type Unknown" << endl; break;
        case Type::STRING: cout << prefix << strValue << endl; break;
        case Type::ARRAY: cout << prefix << "Array[" << array.size() << "]" << endl; break;
        case Type::OBJECT:
            cout << prefix << "Object Map[" << map.size() << "]" << endl;
            if (depth > 0) {
                for (auto element: map) {
                    if (element.second == nullptr) {
                        cout << prefix << "  " << element.first << ": Null entry" << endl;
                    }
                    else {
                        element.second->dumpTree(depth - 1, prefix + "  " + element.first + ": ");
                    }
                }
            }
            break;
    }
}


/**
 * We need to expand this.
 *
 * In the case of name.name, we have an array of strings to select
 * from, and each is a different format of asking for a name. For
 * instance, one of the entries is:
 *
 *			#{prefix} #{first_name} #{last_name}
 *
 * We now have to do something with this. This is ruby-like code,
 * which just works. In C++, this is harder, because each of those
 * are other methods on a name.
 *
 * However, if we just as for a phone_number, we'll get an object map
 * that has a "formats" array of strings where one of those entries is:
 *
 *			###-###-####
 *
 * In this case, we pick one of the formats and then just do string
 * substitution.
 */
std::string
Data::expand(Vector &dataStack) const {
    switch(type) {
        case Type::UNKNOWN: return "";
        case Type::STRING: return expandString(dataStack);
        case Type::ARRAY: return expandArray(dataStack);
        case Type::OBJECT: return expandObject(dataStack);
    }

    // Cant' reach
    return "";
}

/**
 * Expand this string. It might be a simple string or it might have formatting.
 *
 * This is where the magic happens.
 */
std::string
Data::expandString(Vector &dataStack) const {
    string buffer;

    size_t lastPos = 0;
    size_t findPos;

    // This finds all the #{ ... }
    // The funky embedded comments are to balance the braces to help some editors.
    while ( (findPos = strValue.find("#{" /*}*/, lastPos)) != string::npos) {
        // Copy intermediate values.
        if (lastPos < findPos) {
            buffer += strValue.substr(lastPos, findPos - lastPos);
            lastPos = findPos;
        }

        size_t endPos = strValue.find( /*{*/ "}", findPos);
        if (endPos == string::npos) {
            // Had a start with no more ends, so we'll break to grab the rest of the string.
            break;
        }

        string mustRecurseOn = strValue.substr(findPos + 2, endPos-findPos-2);
        lastPos = endPos + 1;

        if ( ::isupper(mustRecurseOn.at(0)) ) {
            string mustRecurseOn_LowerCase = mustRecurseOn;
            std::for_each(mustRecurseOn_LowerCase.begin(), mustRecurseOn_LowerCase.end(), [](char &c) { c = ::tolower(c); });
            string expanded = Base::parse(mustRecurseOn_LowerCase);
            buffer += expanded;
        }
        else {
            int stackSize = dataStack.size();
            if (stackSize > 0) {
                // This might not work if we have dots in these strings.
                Pointer found = nullptr;
                for (int index = stackSize - 1; found == nullptr && index >= 0; --index) {
                    Pointer tryThisOne = dataStack.at(index);
                    found = tryThisOne->find(mustRecurseOn);
                }
                if (found == nullptr) {
                    cout << "expandString() -- Couldn't find: " << mustRecurseOn << endl;
                }
                else {
                    string expanded = found->expand(dataStack);
                    buffer += expanded;
                }
            }
        }
    }

    buffer += strValue.substr(lastPos);

    string retVal;
    for (char const &c: buffer) {
        if (c == '#') {
            retVal += ('0' + Base::randomNumber(0, 9));
        }
        else {
            retVal += c;
        }
    }

    return retVal;
}

/**
 * Our example for this is name.name, where we have an array of recursive ways to do it.
 * But we can also support phone_number.formats.
 */
std::string
Data::expandArray(Vector &dataStack) const {
    Pointer selected = selectFromArray();

    if (selected == nullptr) {
        return "";
    }

    return selected->expand(dataStack);
}

/**
 * Our example for this is phone_number, where we have an array of formats.
 */
std::string
Data::expandObject(Vector &dataStack) const {
    Data::Pointer formats = find("formats");

    if (formats != nullptr) {
        Pointer selected = formats->selectFromArray();
        if (selected == nullptr) {
            return "";
        }

        return selected->expandFormatString(dataStack);
    }

    return "";
}

/**
 * Randomly select from the array.
 */
Data::Pointer
Data::selectFromArray() const {
    size_t size = array.size();

    if (size == 0) {
        return nullptr;
    }

    size_t selectedIndex = Base::randomNumber(0, size - 1);
    Data::Pointer selected = array.at(selectedIndex);

    return selected;
}

/**
 * This works when we're just a format string such as used by phone numbers.
 */
std::string
Data::expandFormatString(Vector &) const {
    return "";
}

//======================================================================
// Utility
//======================================================================

/**
 * Read file contents. Yes, I know, I could do this differently, but I grabbed this somewhere
 * and I'm trying to remain C++ 11 compatible.
 */
std::string readFileContents(const std::string& path) {

    auto close_file = [](FILE* f){fclose(f);};

    auto holder = std::unique_ptr<FILE, decltype(close_file)>(fopen(path.c_str(), "rb"), close_file);
    if (!holder) {
      return "";
    }

    FILE* f = holder.get();

    // in C++17 following lines can be folded into std::filesystem::file_size invocation
    if (fseek(f, 0, SEEK_END) < 0) {
      return "";
    }

    const long size = ftell(f);
    if (size < 0) {
      return "";
    }

    if (fseek(f, 0, SEEK_SET) < 0) {
        return "";
    }

    std::string res;
    res.resize(size);

    // C++17 defines .data() which returns a non-const pointer
    fread(const_cast<char*>(res.data()), 1, size, f);

    return res;
}

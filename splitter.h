// TIE-02006 fall 2017
// Project 01
// Juha Suvanto 189427
// jsuvanto@iki.fi

#ifndef SPLITTER_H
#define SPLITTER_H

#include <string>
#include <vector>

using namespace std;

const unsigned int SPLIT_ERROR = 0;

class Splitter {
    public:

        // Default constructor.
        Splitter(const string& string_to_split = "");

        // Method for changing the string, so we don't need a new splitter
        // object for every string. Effectively resets the object.
        void set_string_to_split(const string& string_to_split);

        // Method for splittin the string.
        unsigned int split(char separator, bool ignore_empty = false);

        // Returns the number of fields.
        unsigned int number_of_fields() const;

        // Returns the substring in a given field.
        string fetch_field(unsigned int field_index) const;

    private:
        string string_to_split_;        // Holds the original string.
        unsigned int number_of_fields_; // Counts the substrings.
        vector<string> substrings_;     // Holds the substrings.
        bool has_been_split_;           // Flag to see if the string is split.
};

#endif // SPLITTER_H

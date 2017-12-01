// TIE-02006 fall 2017
// Project 01
// Juha Suvanto 189427
// jsuvanto@iki.fi

#include "splitter.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// Default constructor. 
// Parameter string_to_split is the string to be split and defaults to "".
Splitter::Splitter(const string& string_to_split):
    string_to_split_(string_to_split),
    number_of_fields_(0),
    has_been_split_(false) {
}


// Replace the string to be split and reinitialize the object.
// Parameter string_to_split is the new string to be split.
void Splitter::set_string_to_split(const string& string_to_split) {
    string_to_split_ = string_to_split; // Set new string.
    substrings_.clear();                // Re-initialize the substring vector.
    number_of_fields_ = 0;              // Re-initialize the number of fields.
    has_been_split_ = false;            // Lower the flag.
}



// Split the string and return the number of substrings.
// Parameter separator is a character that splits the string.
// Parameter ignore_empty is a boolean which controls whether empty
// strings are considered or not.
unsigned int Splitter::split(char separator, bool ignore_empty) {
    string substring;               // Temporary storage for a substring.
    string::size_type position = 0; // Temporary counter for where we are in the string.

    // Find the first separator.
    string::size_type separator_pos = string_to_split_.find(separator);

    // Can we find the separator?
    while (separator_pos != string::npos) {

        // Find the substring between two separators (or begin() and separator).
        substring = string_to_split_.substr(position, separator_pos - position);

        // Only add it if we accept empty strings or it's non-empty.
        if (ignore_empty == false || substring.length() != 0) {
            substrings_.push_back(substring); // Add substring to vector.
            ++number_of_fields_; // Increment the field counter.
        }

        // Find the next separator.
        position = separator_pos + 1; // Start the search behind the most recent separator.
        separator_pos = string_to_split_.find(separator, position);

    }

    // Get the last substring (or the only substring if there are no separators).
    substring = string_to_split_.substr(position);

    // Only add it if we accept empty strings or it's non-empty (same as above)
    if (ignore_empty == false || substring.length() != 0) {
        substrings_.push_back(substring); // Add substring to vector.
        ++number_of_fields_; // Increment the field counter.
    }

    // Raise the flag.
    has_been_split_ = true;

    return number_of_fields_;
}


// Returns the number of substrings.
unsigned int Splitter::number_of_fields() const {

    // Check whether the string has been split. Actually both 
    // number_of_fields; and SPLIT_ERROR equal 0 if it hasn't been 
    // split.
    if (has_been_split_ == true) {
        return number_of_fields_;
    } else {
        return SPLIT_ERROR;
    }
}


// Returns the substring at field_index.
string Splitter::fetch_field(unsigned int field_index) const {

    // Throw an exception if trying to call a field out of range or if
    // the string has not been split yet.
    if (field_index >= number_of_fields_ || !has_been_split_) {
        throw out_of_range("too large index or split not called");
    } else {
        return substrings_.at(field_index);
    }
}

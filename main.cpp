// TIE-02006 fall 2017
// Project 01
// Juha Suvanto 189427
// jsuvanto@iki.fi

#include "date.h"
#include "splitter.h"
#include <string>
#include <iostream>

using namespace std;

string ask_date();

int main() {

    // Create a new default Date object.
    Date this_date;

    bool date_is_valid; // Initialise a flag.

    cout << "--------------------------------" << endl;
    cout << "Welcome to date testing program!" << endl;
    cout << "--------------------------------" << endl;
    cout << endl;

    // Ask a date from the user.
    string input = ask_date();

    // Loop as long as the user doesn't want to quit.
    while (input != "quit") {

        // Create a splitter object from the user input and split it.
        Splitter splitter_object(input);
        splitter_object.split('-');

        // The splitter object must contain exactly three fields.
        if (splitter_object.number_of_fields() != 3) { // Wrong input format.
            date_is_valid = false; // Set the flag to false.
        } else { // Correct input format.

            try { 

                // Attempt to convert the user input from strings to integers.
                unsigned int day = stoi(splitter_object.fetch_field(0));
                unsigned int month = stoi(splitter_object.fetch_field(1));
                unsigned int year = stoi(splitter_object.fetch_field(2));

                // Set the date. Return value (true or false depending on 
                // success) is stored in the flag variable.
                date_is_valid = this_date.set_date(day, month, year);

            } catch (...) {
                // If stoi() fails, the exception is caught here.
                date_is_valid = false;
            }
        }

        // Test output
        cout << "--- TEST OUTPUT BEGIN" << endl;

        if (date_is_valid) {

            // Create a copy for the next date and advance one day forward.
            Date next_date(this_date);
            next_date.forward();

            // Create a copy for the previous date and go one day backward.
            Date prev_date(this_date);
            prev_date.backward();

            // Print information about the date.

            cout << "The date is a valid date." << endl;
            cout << "Day is " << this_date.get_day() << endl;
            cout << "Month is " << this_date.get_month() << endl;
            cout << "Year is " << this_date.get_year() << endl;
            cout << "Weekday is " << this_date.get_weekday() << endl;
            cout << "The previous date was: " << prev_date.get_weekday() << " ";
            prev_date.print();
            cout << "The next date will be: " << next_date.get_weekday() << " ";
            next_date.print();
        } else {
            cout << "Error: this is not a valid date!" << endl;
        }

        cout << "--- TEST OUTPUT END" << endl;
        cout << endl;

        // Ask for a new date.
        input = ask_date();

    } // while (input != quit)

    // End the program because the user has input "quit".
    cout << endl << "Test program ending, goodbye!" << endl;
}

// Ask a date from the user. Returns the input string.
string ask_date() {
    string input;
    cout << "Input a date in day-month-year format: ";
    getline(cin, input);
    return input;
}

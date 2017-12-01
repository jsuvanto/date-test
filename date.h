// TIE-02006 fall 2017
// Project 01
// Juha Suvanto 189427
// jsuvanto@iki.fi

// Declaration of a gregorian date class.

#ifndef DATE_H
#define DATE_H

#include <string>

using namespace std;

const unsigned int DATE_ERROR = false;


class Date {
    public:

        // Default constructor. Create a Date object for Jan 1st AD 1.
        Date();

        // Construct a date from given day, month and year.
        // Parameter year must be 1...9999.
        // Parameter month must be 1...12.
        // Parameter day must be 1...31/30/29/28 depending on month and year.
        Date(const unsigned int& day,
             const unsigned int& month,
             const unsigned int& year);

        // Set a new date from parameters day, month and year.
        // Parameter year must be 1 or greater.
        // Parameter month must be 1...12.
        // Parameter day must be 1...31/30/29/28 depending on month and year.
        // Return true if successful, false if not.
        bool set_date(const unsigned int& day,
                      const unsigned int& month,
                      const unsigned int& year);

        // Return the day.
        unsigned int get_day() const;

        // Return the month.
        unsigned int get_month() const;

        // Return the year.
        unsigned int get_year() const;

        // Print the date in format d.m.yyyy.
        void print() const;

        // Change the date to the next day.
        void forward();

        // Change the date to the previous day.
        void backward();

        // Return the name of the weekday.
        string get_weekday() const;

    private:
        unsigned int day_; // Number of the date's day.
        unsigned int month_; // Number of the date's month.
        unsigned int year_; // Number of the date's year.
        string weekday_; // Name of the dateäs weekday.
};


#endif // DATE_H

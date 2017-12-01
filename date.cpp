// TIE-02006 fall 2017
// Project 01
// Juha Suvanto 189427
// jsuvanto@iki.fi

// Implementation of a gregorian date class.

#include "date.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Declare helper functions.

unsigned int days_in_month(const unsigned int& month,
                           const unsigned int& year);

unsigned int day_of_year(const unsigned int& day,
                         const unsigned int& month,
                         const unsigned int& year);

string calculate_weekday(const unsigned int& day,
                         const unsigned int& month,
                         const unsigned int& year);

int first_weekday_of_year(const unsigned int& year);

bool is_leapyear(const unsigned int& year);


// Implement member functions.

// Create a date for Jan 1st AD 1.
Date::Date(): day_(1), month_(1), year_(1),
              weekday_(calculate_weekday(1, 1, 1)) {
}

// Create a date from parameters.
Date::Date(const unsigned int& day,
           const unsigned int& month,
           const unsigned int& year)
          : day_(), month_(), year_(), weekday_() {

    // Attempt to set the date. Setting an invalid date will leave the 
    // object without a meaningful representation.
    set_date(day, month, year);
}

// Change the date.
bool Date::set_date(const unsigned int& day,
                    const unsigned int& month,
                    const unsigned int& year) {

    // Check validity of the date being set.
    // Year must be 1...9999.
    // Month must be 1...12.
    // Day must be 1...last day of month
    if ( year < 1 || year > 9999
         || month < 1 || month > 12
         || day < 1  || day > days_in_month(month, year)
       ) {
        return DATE_ERROR; // Date is invalid.
    } else {
        // Date is valid.
        year_ = year;
        month_ = month;
        day_ = day;
        weekday_ = calculate_weekday(day_, month_, year_);
        return true;
    }
}


unsigned int Date::get_day() const {
    return day_;
}


unsigned int Date::get_month() const {
    return month_;
}


unsigned int Date::get_year() const {
    return year_;
}


void Date::print() const {
    // Print the date in dd.mm.yyyy format.
    cout << day_ << "." << month_ << "." << year_ << endl;
}


void Date::forward() {
    if (day_ == days_in_month(month_, year_) && month_ == 12) {
        // It's the last day of December.
        // Set date to 1st of Jan, next year.
        set_date(1, 1, year_ + 1);
     } else if (day_ == days_in_month(month_, year_) && month_ != 12)  {
        // It's the last day of some other month.
        // Set date to first day of next month, same year.
        set_date(1, month_ + 1, year_);
    } else {
        // It's not the last day of the month.
        // Set date to next day of same month, same year.
        set_date(day_ + 1, month_, year_);
    }
}


void Date::backward() {
    if (day_ == 1 && month_ == 1) {
        // It's the 1st of January.
        // Set date to 31st of Dec, previous year.
        set_date(31, 12, year_ - 1);
    } else if (day_ == 1 && month_ != 1) {
        // It's the 1st of another month.
        // Set date to the last day of previous month, same year.
        set_date(days_in_month(month_ - 1, year_), month_ - 1, year_);
    } else {
        // It's not the first day of any month.
        // Set date to the previous day, same month, same year.
        set_date(day_ - 1, month_, year_);
    }
}

string Date::get_weekday() const {
    return weekday_;
}


// Implementation of helper functions begins.


// Return the number days in a month.
// Parameter year is required for checking whether it's leap year or not,
// which affects the number of days in February.
unsigned int days_in_month(const unsigned int& month,
                           const unsigned int& year) {
    if (month == 2 && is_leapyear(year)) {
        // It's February on a leap year.
        return 29;
    } else if (month == 2 && !is_leapyear(year)) {
        // It's February on a regular year.
        return 28;
    } else if (month == 4           // It's April.
               || month == 6        // It's June.
               || month == 9        // It's September.
               || month == 11) {    // It's November.
        return 30;
    } else {
        // It's some other month.
        return 31;
    }
}


// Return true if parameter year is a leap year, false if not.
bool is_leapyear(const unsigned int& year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return true;
    } else {
        return false;
    }
}


// Return the name of the weekday. Parameters day, month, year.
string calculate_weekday(const unsigned int& day,
                         const unsigned int& month, 
                         const unsigned int& year) {

    // Store the names of weekdays for easy lookup.
    const vector<string> day_names = {"Sunday", "Monday", "Tuesday", 
                                      "Wednesday", "Thursday", "Friday", 
                                      "Saturday"};

    // Calculate which weekday it is. 0 = Sunday, 6 = Saturday.
    // First calculate what day the year starts on. Then add how many 
    // days have passed since the start of the year. Then, remove one day
    // because effectively Jan 1st is counted twice. Finally, mod 7 to
    // remove full weeks.
    int weekday = ( first_weekday_of_year(year)
                    + day_of_year(day, month, year)
                    - 1 // Jan 1st is counted twice!
                  ) % 7; // Remove full weeks.

    return day_names[weekday];
}


// Calculate how many days, including this one, have passed since
// start of year. Parameters day, month and year.
unsigned int day_of_year(const unsigned int& day,
                         const unsigned int& month,
                         const unsigned int& year) {
    unsigned int days = 0; // Initialise a counter.

    // Add each full month before current one to the counter.
    for (unsigned int i = 1; i < month; i++) {
        days += days_in_month(i, year);
    }

    days += day; // Add this month's days.
    return days;
}


// Calculate the first weekday of the parameter year.
// Returns an integer 0...6 where 0 = Sunday and 6 = Saturday.
// This uses Gauss's algorithm:
// https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Gauss.27s_algorithm

int first_weekday_of_year(const unsigned int& year) {
    return ( 1
             + 5 * ((year - 1) % 4)
             + 4 * ((year - 1) % 100)
             + 6 * ((year - 1) % 400)
           ) % 7;
}

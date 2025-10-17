
#ifndef DATE_H
#define DATE_H

#include <string>

struct Date {
    int y{ 0 }, m{ 0 }, d{ 0 };
};

namespace DateUtil {

    // Parse "YYYY-MM-DD" string into Date struct; returns true on format success only
    bool parseISO(const std::string& iso, Date& out);

    // Validate an actual calendar date (month lengths, leap years)
    bool isValid(const Date& dt);

    // Return true if both Dates are the same calendar day
    bool sameDay(const Date& a, const Date& b);

    // Return nonnegative days between Dates (order independent)
    int daysBetween(const Date& a, const Date& b);

    // Return true if year is a leap year according to Gregorian rules
    bool isLeap(int year);

    // Return number of days in month for given year (handles leap year February)
    int monthLen(int month, int year);

    // Convert Date to serial day count from year 1-01-01 (for daysBetween)
    int toSerial(const Date& dt);

    // Convert Date back to ISO string "YYYY-MM-DD" with zero padding month/day 1-9
    std::string toISO(const Date& dt);

} // namespace DateUtil

#endif // DATE_H


#include "Date.h"
#include <cctype>
#include <cstdlib>

// TODO: Implement leap-year detection, month lengths, and a serial-day conversion
// to support isValid() and daysBetween(). See assignment spec for requirements.

namespace DateUtil {

bool parseISO(const std::string& s, Date& out) {
    // Enforce "YYYY-MM-DD" with digits in the correct positions
    if (s.size() != 10 || s[4] != '-' || s[7] != '-') return false;
    for (int i : {0,1,2,3,5,6,8,9}) if (!std::isdigit((unsigned char)s[i])) return false;
    out.y = std::atoi(s.substr(0,4).c_str());
    out.m = std::atoi(s.substr(5,2).c_str());
    out.d = std::atoi(s.substr(8,2).c_str());
    return true;
}

bool isValid(const Date& dt) {
    // TODO: return true only if dt is a real calendar date (handle leap years)
    // Replace the placeholder below.
    return false;
}

bool sameDay(const Date& a, const Date& b) {
    // Exact same calendar date
    return (a.y == b.y) && (a.m == b.m) && (a.d == b.d);
}

int daysBetween(const Date& a, const Date& b) {
    // TODO: compute nonnegative difference in days between a and b.
    // You may implement via a serial-day function (e.g., Rata Die).
    // Replace the placeholder below.
    return 0;
}

} // namespace DateUtil

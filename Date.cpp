
#include "Date.h"
#include <string>
#include <cstdlib>  // for atoi
#include <cctype>   // for isdigit
#include <cstdio>   // for snprintf

namespace DateUtil {

    bool isLeap(int year) {
        if (year % 4 != 0) return false;
        if (year % 100 != 0) return true;
        if (year % 400 == 0) return true;
        return false;
    }

    int monthLen(int month, int year) {
        if (month == 2) {
            return isLeap(year) ? 29 : 28;
        }
        if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
        return 31;
    }

    bool parseISO(const std::string& s, Date& out) {
        // Format must be exactly 10 chars: "YYYY-MM-DD"
        if (s.size() != 10 || s[4] != '-' || s[7] != '-') return false;
        for (int i : {0, 1, 2, 3, 5, 6, 8, 9}) {
            if (!std::isdigit((unsigned char)s[i])) return false;
        }
        out.y = std::atoi(s.substr(0, 4).c_str());
        out.m = std::atoi(s.substr(5, 2).c_str());
        out.d = std::atoi(s.substr(8, 2).c_str());
        return true;
    }

    bool isValid(const Date& dt) {
        if (dt.y < 1 || dt.m < 1 || dt.m > 12 || dt.d < 1) return false;
        if (dt.d > monthLen(dt.m, dt.y)) return false;
        return true;
    }

    bool sameDay(const Date& a, const Date& b) {
        return (a.y == b.y) && (a.m == b.m) && (a.d == b.d);
    }

    int toSerial(const Date& dt) {
        int total = 0;
        for (int y = 1; y < dt.y; ++y) {
            total += isLeap(y) ? 366 : 365;
        }
        for (int m = 1; m < dt.m; ++m) {
            total += monthLen(m, dt.y);
        }
        total += dt.d;
        return total;
    }

    int daysBetween(const Date& a, const Date& b) {
        int serialA = toSerial(a);
        int serialB = toSerial(b);
        return serialA > serialB ? serialA - serialB : serialB - serialA;
    }

    std::string toISO(const Date& dt) {
        // Format YYYY-MM-DD with zero-padding for month and day if needed
        char buf[11];
        // snprintf with %02d for zero-padding days and months 1-9
        std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d", dt.y, dt.m, dt.d);
        return std::string(buf);
    }

} // namespace DateUtil
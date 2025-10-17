
#ifndef BLOOD_DONATION_H
#define BLOOD_DONATION_H

#include <string>
#include <iostream>
#include "Date.h"

namespace Result {
    static const std::string OK = "OK";
    static const std::string BAD_ID = "BAD_ID";
    static const std::string BAD_AGE = "BAD_AGE";
    static const std::string BAD_WEIGHT = "BAD_WEIGHT";
    static const std::string BAD_DATE = "BAD_DATE";
    static const std::string SAME_DAY = "SAME_DAY";   
    static const std::string TOO_SOON = "TOO_SOON";
}

class BloodDonation {
public:
    BloodDonation(const std::string& idStr, int ageYears, double weightLb, const std::string& dateISO);

    const std::string& id() const;
    int age() const;
    double weight() const;
    const Date& date() const;

    std::string validate() const;

    // Intentionally minimal 
    void print() const {}

private:
    std::string m_id;
    int m_age;
    double m_weight;
    Date m_date;
};

#endif // BLOOD_DONATION_H

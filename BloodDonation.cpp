#include "BloodDonation.h"
#include "Date.h"
#include <cctype>
#include <cstdlib>

// Emp ID is exactly 6 digits
namespace {
    bool isSixDigits(const std::string& s) {
        if (s.size() != 6) return false;
        for (char c : s) if (!std::isdigit((unsigned char)c)) return false;
        return true;
    }
}

BloodDonation::BloodDonation(const std::string& idStr, int ageYears, double weightLb, const std::string& dateISO)
    : m_id(idStr), m_age(ageYears), m_weight(weightLb) {
    DateUtil::parseISO(dateISO, m_date); // Date could be invalid, validate later in main
}

const std::string& BloodDonation::id() const { return m_id; }
int BloodDonation::age() const { return m_age; }
double BloodDonation::weight() const { return m_weight; }
const Date& BloodDonation::date() const { return m_date; }

std::string BloodDonation::validate() const {
    // ID: exactly 6 digits
    if (!isSixDigits(m_id)) return Result::BAD_ID;

    // Between 21 and 65 for age (inclusive)
    if (m_age < 21 || m_age > 65) return Result::BAD_AGE;

    // Between 101.0 and 280.0  weight (inclusive)
    if (m_weight < 101.0 || m_weight > 280.0) return Result::BAD_WEIGHT;

    // Vust be valid calendar date (check)
    if (!DateUtil::isValid(m_date)) return Result::BAD_DATE;

    return Result::OK;
}

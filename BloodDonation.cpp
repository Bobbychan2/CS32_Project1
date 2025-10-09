
#include "BloodDonation.h"
#include <cctype>
#include <cstdlib>

// Simpler helper (no namespace tricks):
static bool isSixDigits(const std::string& s) {
    if (s.size() != 6) return false;
    for (size_t i = 0; i < s.size(); ++i) {
        if (!std::isdigit((unsigned char)s[i])) return false;
    }
    return true;
}

BloodDonation::BloodDonation(const std::string& idStr, int ageYears, double weightLb, const std::string& dateISO)
: m_id(idStr), m_age(ageYears), m_weight(weightLb)
{
    // Parse into m_date but do not validate here.
    DateUtil::parseISO(dateISO, m_date);
}

const std::string& BloodDonation::id() const { return m_id; }
int BloodDonation::age() const { return m_age; }
double BloodDonation::weight() const { return m_weight; }
const Date& BloodDonation::date() const { return m_date; }

std::string BloodDonation::validate() const {
    // TODO: implement field validation per spec
    // ID: exactly 6 digits
    // Age: [21, 65]
    // Weight: [101.0, 280.0]
    // Date: must be a valid calendar date
    // Replace the placeholder below with real checks.
    (void)isSixDigits; // silence unused warning until implemented
    if (!DateUtil::isValid(m_date)) return Result::BAD_DATE; // placeholder partial
    return Result::OK;
}

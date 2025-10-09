
#include "VacationAccount.h"

namespace {
    const int MIN_INTERVAL_DAYS = 180;
    const double HOURS_PER_DONATION = 4.0;
}

VacationAccount::VacationAccount(const std::string& donorId)
: m_id(donorId), m_items(nullptr), m_size(0), m_capacity(0), m_hours(0.0)
{
    // TODO: optional: validate donorId format; account-level ID check occurs in add()
}

VacationAccount::~VacationAccount() {
    // TODO: delete owned BloodDonation pointers and array
}

VacationAccount::VacationAccount(const VacationAccount& other)
: m_id(other.m_id), m_items(nullptr), m_size(0), m_capacity(0), m_hours(0.0)
{
    // TODO: deep copy other's donations and hours
}

VacationAccount& VacationAccount::operator=(const VacationAccount& other) {
    if (this != &other) {
        // TODO: release current resources and deep copy from other
    }
    return *this;
}

void VacationAccount::ensureCapacity(int need) {
    // TODO: grow to at least 'need' capacity (simple +1 growth is acceptable)
}

void VacationAccount::clear() {
    // TODO: delete owned donations, delete array, reset fields
}

void VacationAccount::deepCopyFrom(const VacationAccount& other) {
    // TODO: allocate new array and deep-copy each BloodDonation
}

const std::string& VacationAccount::id() const { return m_id; }
double VacationAccount::balanceHours() const { return m_hours; }
int VacationAccount::size() const { return m_size; }

const BloodDonation* VacationAccount::at(int index) const {
    if (index < 0 || index >= m_size) return nullptr;
    return m_items[index];
}

std::string VacationAccount::add(const BloodDonation& donation) {
    // TODO: Implement in this exact order:
    // 1) Independent validation (donation.validate()). If not OK, return that code.
    // 2) Account ID equality: if donation.id() != m_id, return BAD_ID.
    // 3) SAME_DAY: if any accepted donation has the same calendar date, return "SAME_DAY".
    // 4) TOO_SOON: if daysBetween(lastAccepted, donation.date()) < 180, return "TOO_SOON".
    // 5) On success: deep-copy, append to array, increment hours by +4.0, return OK.
    return Result::OK; // placeholder
}

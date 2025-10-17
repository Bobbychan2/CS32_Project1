#include "VacationAccount.h"
#include "Date.h"
#include <string>
#include <cstdlib>

namespace {
    const int MIN_INTERVAL_DAYS = 180;
    const double HOURS_PER_DONATION = 4.0;
}

VacationAccount::VacationAccount(const std::string& donorId)
    : m_id(donorId), m_items(nullptr), m_size(0), m_capacity(0), m_hours(0.0) {
}

VacationAccount::~VacationAccount() {
    clear();
}

VacationAccount::VacationAccount(const VacationAccount& other)
    : m_id(other.m_id), m_items(nullptr), m_size(0), m_capacity(0), m_hours(0.0) {
    deepCopyFrom(other);
}

VacationAccount& VacationAccount::operator=(const VacationAccount& other) {
    if (this != &other) {
        clear();
        m_id = other.m_id;
        deepCopyFrom(other);
    }
    return *this;
}

void VacationAccount::ensureCapacity(int need) {
    if (need <= m_capacity) return;

    int newCapacity = std::max(1, m_capacity * 2);
    while (newCapacity < need) {
        newCapacity *= 2;
    }

    BloodDonation** newItems = new BloodDonation * [newCapacity];
    for (int i = 0; i < m_size; ++i) {
        newItems[i] = m_items[i];
    }
    delete[] m_items;
    m_items = newItems;
    m_capacity = newCapacity;
}

//Deletes each stored copy of BloodDonation* and arrays used to store them

void VacationAccount::clear() { 
    if (m_items != nullptr) {
        for (int i = 0; i < m_size; ++i) {
            delete m_items[i];
        }
        delete[] m_items;
        m_items = nullptr;
    }
    m_size = 0;
    m_capacity = 0;
    m_hours = 0.0;
}

void VacationAccount::deepCopyFrom(const VacationAccount& other) {
    ensureCapacity(other.m_size);
    for (int i = 0; i < other.m_size; ++i) {
        m_items[i] = new BloodDonation(*other.m_items[i]);
    }
    m_size = other.m_size;
    m_hours = other.m_hours;
}

std::string VacationAccount::add(const BloodDonation& donation) {
    std::string validationResult = donation.validate();
    if (validationResult != Result::OK) return validationResult;

    if (donation.id() != m_id) return Result::BAD_ID;

    for (int i = 0; i < m_size; ++i) {
        if (DateUtil::sameDay(m_items[i]->date(), donation.date())) {
            //std::cout << "Rejecting same day donation: existing date " // Used for debugging
               // << DateUtil::toISO(m_items[i]->date())
              //  << ", new date " << DateUtil::toISO(donation.date()) << std::endl;
            return Result::SAME_DAY;
        }
    } 

    int newSerial = DateUtil::toSerial(donation.date());
    for (int i = 0; i < m_size; ++i) {
        int existingSerial = DateUtil::toSerial(m_items[i]->date());
        int diff = newSerial - existingSerial;
        if (diff > 0 && diff < MIN_INTERVAL_DAYS) {  // Only check if new after existing donation
            return Result::TOO_SOON;
        }
    }

    ensureCapacity(m_size + 1);

    m_items[m_size] = new BloodDonation(donation);
    ++m_size;
    m_hours += HOURS_PER_DONATION;

    // std::cout << "Donation added: new size = " << m_size << ", hours = " << m_hours << std::endl; // Debugging only

    return Result::OK;
}

int VacationAccount::size() const {
    return m_size;
}

double VacationAccount::balanceHours() const {
    return m_hours;
}
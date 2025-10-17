#ifndef VACATION_ACCOUNT_H
#define VACATION_ACCOUNT_H

#include <string>
#include "BloodDonation.h"

class VacationAccount {
public:
    explicit VacationAccount(const std::string& donorId);
    ~VacationAccount();
    VacationAccount(const VacationAccount& other);
    VacationAccount& operator=(const VacationAccount& other);

    std::string add(const BloodDonation& donation);

    int size() const;
    double balanceHours() const;

private:
    std::string m_id;
    BloodDonation** m_items;  // dynamic array of pointers to donations
    int m_size;
    int m_capacity;
    double m_hours;

    void ensureCapacity(int need);
    void clear();
    void deepCopyFrom(const VacationAccount& other);
};

#endif // VACATION_ACCOUNT_H


#include "VacationAccount.h"
#include <cassert>

int main() {
    // Minimal starter; you must add >= 15 assertions to cover all rules.

    // --- Example tests (uncomment after you implement the corresponding functions) ---
    /*
    VacationAccount acc("123456");
    BloodDonation good("123456", 30, 150.0, "2025-01-01");
    assert(good.validate() == "OK");               // field validation
    assert(acc.add(good) == "OK");                 // account-level acceptance
    assert(acc.size() == 1);                       // size increments
    assert(acc.balanceHours() == 4.0);             // +4 hours credit

    BloodDonation badIdFmt("12A456", 30, 150.0, "2025-01-02");
    assert(badIdFmt.validate() == "BAD_ID");       // invalid ID format

    BloodDonation mismatch("654321", 30, 150.0, "2025-07-01");
    assert(mismatch.validate() == "OK");
    assert(acc.add(mismatch) == "BAD_ID");         // account-level id mismatch

    BloodDonation sameDay("123456", 30, 150.0, "2025-01-01");
    assert(acc.add(sameDay) == "SAME_DAY");        // duplicate calendar date

    BloodDonation tooSoon("123456", 30, 150.0, "2025-06-29");
    assert(tooSoon.validate() == "OK");
    assert(acc.add(tooSoon) == "TOO_SOON");        // < 180 days since last accepted
    */

    return 0;
}

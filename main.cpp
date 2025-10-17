
#include "VacationAccount.h"
#include <cassert>


int main() {
    
using namespace DateUtil;

    // Test leap year 
    assert(isLeap(2024) == true);
    assert(isLeap(1900) == false);
    assert(isLeap(2000) == true);
    assert(isLeap(2100) == false);

    // Test month lengths (including February leap year on leap year)
    assert(monthLen(2, 2024) == 29);
    assert(monthLen(2, 2025) == 28);
    assert(monthLen(4, 2025) == 30);
    assert(monthLen(1, 2025) == 31);

    // Test valid and invalid dates
    Date d1{ 2024, 2, 29 };
    Date d2{ 2025, 2, 29 };
    assert(isValid(d1) == true);
    assert(isValid(d2) == false);

    // Test sameDay function
    Date d3{ 2025, 1, 1 };
    Date d4{ 2025, 1, 1 };
    Date d5{ 2025, 1, 2 };
    assert(sameDay(d3, d4) == true);
    assert(sameDay(d3, d5) == false);

    // Test daysBetween function
    assert(daysBetween(d3, d5) == 1);
    assert(daysBetween(d5, d3) == 1);

    // Test parseISO and toISO functions
    Date parsedDate;
    assert(parseISO("2025-10-11", parsedDate));
    assert(parsedDate.y == 2025 && parsedDate.m == 10 && parsedDate.d == 11);

    std::string isoStr = toISO(parsedDate);
    assert(isoStr == "2025-10-11");

    // Test zero padding in toISO
    Date paddedDate{ 2025, 4, 9 };
    assert(toISO(paddedDate) == "2025-04-09");

    // Minimal starter; you must add >= 15 assertions to cover all rules.

    // --- Example tests (uncomment after you implement the corresponding functions) ---
   
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

    BloodDonation dayAfter("123456", 30, 150.0, "2025-01-02");
    assert(acc.add(dayAfter) == "TOO_SOON");              // ADDED THIS TEST CASE

    BloodDonation tooSoon("123456", 30, 150.0, "2025-06-29");
    assert(tooSoon.validate() == "OK");
    assert(acc.add(tooSoon) == "TOO_SOON");        // < 180 days since last accepted

    //---------------------ADDITIONAL TEST CASES---------------------//

    BloodDonation badId("ABC123", 40, 150.0, "2025-06-01");
    assert(badId.validate() == "BAD_ID");

    // Invalid weight
    BloodDonation lowWeight("123456", 40, 100.0, "2025-06-01");
    assert(lowWeight.validate() == "BAD_WEIGHT");

    BloodDonation highWeight("123456", 40, 281.0, "2025-06-01");
    assert(highWeight.validate() == "BAD_WEIGHT");

    // Invalid age
    BloodDonation tooYoung("123456", 20, 150.0, "2025-06-01");
    assert(tooYoung.validate() == "BAD_AGE");

    // Invalid date
    BloodDonation badDate("123456", 40, 150.0, "2025-02-30");  
    assert(badDate.validate() == "BAD_DATE");

    //---------------------Test blood donation---------------------//

    // First valid donation
    VacationAccount SuperBloodDonor("987654");

    BloodDonation valid1("987654", 40, 150.0, "2025-01-01");
    assert(SuperBloodDonor.add(valid1) == "OK");
    
    // Add another valid donation after enough time elapsed (e.g., 180+ days)
    BloodDonation valid2("987654", 40, 150.0, "2025-07-01");
    assert(SuperBloodDonor.add(valid2) == "OK");

    //---------------------Account Management---------------------//

    VacationAccount VacationMaster("111111");

    // VALID donation matching employee ID should be accepted
    BloodDonation validDonation("111111", 30, 150.0, "2025-01-01");
    assert(validDonation.validate() == "OK");
    assert(VacationMaster.add(validDonation) == "OK");
    assert(VacationMaster.size() == 1);            // One accepted donation
    assert(VacationMaster.balanceHours() == 4.0);  // 4 vacation hours added

    // INVALID donation with mismatched ID should be rejected
    BloodDonation invalidIDDonation("222222", 30, 150.0, "2025-07-01");
    assert(invalidIDDonation.validate() == "OK");
    assert(VacationMaster.add(invalidIDDonation) == "BAD_ID"); // Expect rejection
    assert(VacationMaster.size() == 1);             // Size unchanged
    assert(VacationMaster.balanceHours() == 4.0);   // Hours unchanged

    // Another VALID donation with correct ID and sufficient spacing
    BloodDonation validDonation2("111111", 30, 150.0, "2025-07-01");
    assert(validDonation2.validate() == "OK");
    assert(VacationMaster.add(validDonation2) == "OK");
    assert(VacationMaster.size() == 2);             // Two accepted donations
    assert(VacationMaster.balanceHours() == 8.0);   // 8 vacation hours accumulated

    // Attempt a valid donation but too soon after last valid donation
    BloodDonation tooSoonDonation("111111", 30, 150.0, "2025-08-01");
    assert(tooSoonDonation.validate() == "OK");
    assert(VacationMaster.add(tooSoonDonation) == "TOO_SOON"); // Expect rejection
    assert(VacationMaster.size() == 2);            // Size unchanged
    assert(VacationMaster.balanceHours() == 8.0); // Hours unchanged

    // Testing object destruction
    VacationAccount acc1("123456");
    acc1.add(BloodDonation("123456", 30, 150.0, "2025-01-01"));

    // Test copy c'tor
    VacationAccount acc2(acc1); 
    acc1.add(BloodDonation("123456", 31, 160.0, "2025-07-01"));

    assert(acc2.size() == 1); // acc2 should remain unchanged

    // Test AO
    VacationAccount acc3("000000");
    acc3 = acc1; 
    assert(acc3.size() == acc1.size());
 
return 0;
}
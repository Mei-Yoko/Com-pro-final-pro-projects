#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "license.h"


void test_isValidDateFormat() {
    assert(isValidDateFormat("2025-10-09") == 1);
    assert(isValidDateFormat("1999-01-01") == 1);
    assert(isValidDateFormat("2025-02-30") == 0);
    assert(isValidDateFormat("25-10-09") == 0);   
    assert(isValidDateFormat("2025/10/09") == 0); 
    printf("✓ test_isValidDateFormat passed\n");
}

void test_isDuplicateID() {
    LicenseRequest records[3] = {
        {"L001", "John Doe", "TypeA", "2025-08-01"},
        {"L003", "Marcus Rashford", "TypeB", "2025-10-02"},
        {"L004", "Charlie", "TypeC", "2025-10-03"}
    };
    assert(isDuplicateID(records, 3, "L002") == 1);
    assert(isDuplicateID(records, 3, "L999") == 0);
    printf("✓ test_isDuplicateID passed\n");
}

void test_trim_and_isEmpty() {
    char test1[] = "  hello ";
    trim(test1);
    assert(strcmp(test1, "hello") == 0);

    char test2[] = "    ";
    assert(isEmpty(test2) == 1);
    printf("✓ test_trim_and_isEmpty passed\n");
}

void test_write_and_read_CSV() {
    LicenseRequest records[2] = {
        {"L001", "Test1", "TypeA", "2025-10-01"},
        {"L002", "Test2", "TypeB", "2025-10-02"}
    };
    writeCSV(records, 2);

    LicenseRequest loaded[10];
    int count = readCSV(loaded);
    assert(count == 2);
    assert(strcmp(loaded[0].requestID, "REQ001") == 0);
    assert(strcmp(loaded[1].licenseType, "TypeB") == 0);
    printf("✓ test_write_and_read_CSV passed\n");
}


int run_unit_tests(void) {
    printf("=== Running Unit Tests ===\n");
    test_isValidDateFormat();
    test_isDuplicateID();
    test_trim_and_isEmpty();
    test_write_and_read_CSV();
    printf(" All unit tests passed successfully!\n");
    return 0;
}

int main() {
    return run_unit_tests();
}

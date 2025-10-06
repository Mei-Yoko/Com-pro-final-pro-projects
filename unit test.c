#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "Final Project CECS.c"  

void test_isValidDateFormat() {
    assert(isValidDateFormat("2025-10-06") == 1);
    assert(isValidDateFormat("2025-13-01") == 1); // ยังไม่ตรวจค่าจริงของเดือน แต่ควรผ่าน format
    assert(isValidDateFormat("25-10-06") == 0);
    assert(isValidDateFormat("2025/10/06") == 0);
    assert(isValidDateFormat("abcd-ef-gh") == 0);
    printf(" test_isValidDateFormat passed!\n");
}

void test_addRecord() {
    LicenseRequest records[10];
    int count = 0;

    LicenseRequest mock = {"REQ001", "Alice", "Software", "2025-10-06"};
    records[count++] = mock;
    assert(strcmp(records[0].requestID, "L01") == 0);
    assert(strcmp(records[0].requesterName, "Alice") == 0);
    printf(" test_addRecord passed!\n");
}

void test_searchRecord_partial() {
    LicenseRequest records[3] = {
        {"L001", "Alice", "IT", "2025-10-06"},
        {"L002", "Bob", "Driver", "2025-10-06"},
        {"L003", "Alicia", "Business", "2025-10-06"}
    };
    char keyword[] = "Ali";
    int found = 0;

    for (int i = 0; i < 3; i++) {
        if (strstr(records[i].requesterName, keyword)) {
            found++;
        }
    }

    assert(found == 2);
    printf(" test_searchRecord_partial passed!\n");
}

void test_loginSystem() {
    User mockUsers[3] = {
        {"admin", "1234", "Admin"},
        {"staff", "1234", "Staff"},
        {"user", "1234", "General"}
    };

    User loginUser;
    int found = 0;
    for (int i = 0; i < 3; i++) {
        if (strcmp(mockUsers[i].username, "admin") == 0 &&
            strcmp(mockUsers[i].password, "1234") == 0) {
            loginUser = mockUsers[i];
            found = 1;
            break;
        }
    }

    assert(found == 1);
    assert(strcmp(loginUser.role, "Admin") == 0);
    printf(" test_loginSystem passed!\n");
}

void test_deleteRecord() {
    LicenseRequest records[3] = {
        {"L001", "Alice", "IT", "2025-10-06"},
        {"L002", "Bob", "Driver", "2025-10-06"},
        {"L003", "Chris", "Admin", "2025-10-06"}
    };
    int count = 3;
    char target[] = "002";

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].requestID, target) == 0) {
            for (int j = i; j < count - 1; j++) {
                records[j] = records[j + 1];
            }
            count--;
            found = 1;
            break;
        }
    }

    assert(found == 1);
    assert(count == 2);
    assert(strcmp(records[1].requestID, "003") == 0);
    printf(" test_deleteRecord passed!\n");
}


#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "license.h"

#define TEST_FILE "test_data.csv"

void prepare_test_file() {
    FILE *f = fopen(TEST_FILE, "w");
    fprintf(f, "RequestID,RequesterName,LicenseType,RequestDate\n");
    fprintf(f, "L001,John Doe,Business License,2025-08-01\n");
    fprintf(f, "L003,Marcus Rashford,Event Permit,2025-08-04\n");
    fprintf(f, "L004,Luke Shaw,Business License,2025-08-06\n");
    fclose(f);
}

void test_read_csv() {
    LicenseRequest records[MAX_RECORDS];
    int count = readCSV(records);
    assert(count > 0);
    assert(strcmp(records[0].requestID, "L001") == 0);
    printf(" test_read_csv ผ่านแล้ว\n");
}


void test_add_record() {
    LicenseRequest records[MAX_RECORDS];
    int count = readCSV(records);

    LicenseRequest newRec = {"REQ999", "TestUser", "Firewall", "2025-12-25"};
    records[count] = newRec;
    count++;
    writeCSV(records, count);

    LicenseRequest verify[MAX_RECORDS];
    int newCount = readCSV(verify);
    assert(newCount == count);
    assert(strcmp(verify[newCount - 1].requestID, "L999") == 0);
    printf(" test_add_record ผ่านแล้ว\n");
}


void test_update_record() {
    LicenseRequest records[MAX_RECORDS];
    int count = readCSV(records);
    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].requestID, "L002") == 0) {
            strcpy(records[i].licenseType, "Cloud");
        }
    }
    writeCSV(records, count);

    LicenseRequest verify[MAX_RECORDS];
    readCSV(verify);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(verify[i].requestID, "L002") == 0) {
            assert(strcmp(verify[i].licenseType, "Cloud") == 0);
            found = 1;
        }
    }
    assert(found);
    printf("✔ test_update_record ผ่านแล้ว\n");
}

void test_delete_record() {
    LicenseRequest records[MAX_RECORDS];
    int count = readCSV(records);
    int delIndex = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].requestID, "L003") == 0) {
            delIndex = i;
        }
    }
    assert(delIndex != -1);
    for (int j = delIndex; j < count - 1; j++) {
        records[j] = records[j + 1];
    }
    count--;
    writeCSV(records, count);

    LicenseRequest verify[MAX_RECORDS];
    int newCount = readCSV(verify);
    for (int i = 0; i < newCount; i++) {
        assert(strcmp(verify[i].requestID, "L003") != 0);
    }
    printf("✔ test_delete_record ผ่านแล้ว\n");
}

void test_search_record() {
    LicenseRequest records[MAX_RECORDS];
    int count = readCSV(records);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(records[i].requesterName, "Alice")) {
            found = 1;
        }
    }
    assert(found);
    printf(" test_search_record ผ่านแล้ว\n");
}

int main() {
    printf("เริ่มการทดสอบ End-to-End...\n");

    prepare_test_file();
    test_read_csv();
    test_add_record();
    test_update_record();
    test_delete_record();
    test_search_record();

    printf(" การทดสอบทั้งหมดผ่านเรียบร้อย!\n");
    return 0;
}

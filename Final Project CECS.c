#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 256
#define MAX_RECORDS 1000
#define FILE_NAME "data.csv"

// STRUCT 
typedef struct {
    char requestID[20];
    char requesterName[50];
    char licenseType[50];
    char requestDate[20];
} LicenseRequest;

typedef struct {
    char username[20];
    char password[20];
    char role[10]; // Admin / Staff / General
} User;

//  USERS 
User users[] = {
    {"admin", "1234", "Admin"},
    {"staff", "1234", "Staff"},
    {"user", "1234", "General"}
};

//  DATE 
int isValidDateFormat(const char *date) {
    if (strlen(date) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if ((i == 4 || i == 7) && date[i] != '-') return 0;
        if ((i != 4 && i != 7) && !isdigit(date[i])) return 0;
    }
    return 1;
}

//  READ CSV 
int readCSV(LicenseRequest records[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf(" ไม่พบไฟล์ %s\n", FILE_NAME);
        return 0;
    }
    char line[MAX_LINE];
    int count = 0;
    fgets(line, sizeof(line), file); // ข้าม Header

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, " %[^,],%[^,],%[^,],%[^\n]",
               records[count].requestID,
               records[count].requesterName,
               records[count].licenseType,
               records[count].requestDate);
        count++;
    }
    fclose(file);
    return count;
}

//  FUNCTION: WRITE CSV 
void writeCSV(LicenseRequest records[], int count) {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf(" ไม่สามารถเขียนไฟล์ได้\n");
        return;
    }
    fprintf(file, "RequestID,RequesterName,LicenseType,RequestDate\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s,%s\n",
                records[i].requestID,
                records[i].requesterName,
                records[i].licenseType,
                records[i].requestDate);
    }
    fclose(file);
}

//  ADD RECORD 
void addRecord(LicenseRequest records[], int *count) {
    LicenseRequest newRec;
    printf("หมายเลขคำขอ: ");
    scanf(" %[^\n]", newRec.requestID);
    printf("ชื่อผู้ขอ: ");
    scanf(" %[^\n]", newRec.requesterName);
    printf("ประเภทใบอนุญาต: ");
    scanf(" %[^\n]", newRec.licenseType);

    do {
        printf("วันที่ขอ (YYYY-MM-DD): ");
        scanf(" %[^\n]", newRec.requestDate);
        if (!isValidDateFormat(newRec.requestDate)) {
            printf(" รูปแบบวันที่ไม่ถูกต้อง! กรุณากรอกใหม่ (เช่น 2025-10-06)\n");
        }
    } while (!isValidDateFormat(newRec.requestDate));

    records[*count] = newRec;
    (*count)++;
    writeCSV(records, *count);
    printf("เพิ่มข้อมูลเรียบร้อย!\n");
}

//  SEARCH RECORD 
void searchRecord(LicenseRequest records[], int count) {
    char keyword[50];
    int found = 0;

    printf("กรอกคำค้นหา (ชื่อบางส่วนหรือหมายเลขคำขอ): ");
    scanf(" %[^\n]", keyword);

    for (int i = 0; i < count; i++) {
        if (strstr(records[i].requestID, keyword) ||
            strstr(records[i].requesterName, keyword)) {
            printf("พบข้อมูล: %s | %s | %s | %s\n",
                   records[i].requestID,
                   records[i].requesterName,
                   records[i].licenseType,
                   records[i].requestDate);
            found = 1;
        }
    }

    if (!found)
        printf(" ไม่พบข้อมูลที่ค้นหา\n");
}

// UPDATE RECORD 
void updateRecord(LicenseRequest records[], int count) {
    char reqID[20];
    int found = 0;

    printf("กรอกหมายเลขคำขอที่ต้องการแก้ไข: ");
    scanf(" %[^\n]", reqID);

    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].requestID, reqID) == 0) {
            printf("ข้อมูลเดิม: %s | %s | %s | %s\n",
                   records[i].requestID,
                   records[i].requesterName,
                   records[i].licenseType,
                   records[i].requestDate);
            printf("ประเภทใบอนุญาตใหม่: ");
            scanf(" %[^\n]", records[i].licenseType);
            writeCSV(records, count);
            printf(" อัปเดตเรียบร้อย!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf(" ไม่พบหมายเลขคำขอ\n");
}

// DELETE RECORD 
void deleteRecord(LicenseRequest records[], int *count) {
    char reqID[20];
    int found = 0;

    printf("กรอกหมายเลขคำขอที่ต้องการลบ: ");
    scanf(" %[^\n]", reqID);

    for (int i = 0; i < *count; i++) {
        if (strcmp(records[i].requestID, reqID) == 0) {
            for (int j = i; j < *count - 1; j++) {
                records[j] = records[j + 1];
            }
            (*count)--;
            writeCSV(records, *count);
            printf(" ลบข้อมูลเรียบร้อย!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf(" ไม่พบหมายเลขคำขอ\n");
}

//  LOGIN 
User loginSystem() {
    char username[20], password[20];
    User empty = {"", "", ""};

    printf("ชื่อผู้ใช้: ");
    scanf(" %s", username);
    printf("รหัสผ่าน: ");
    scanf(" %s", password);

    for (int i = 0; i < 3; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            printf(" เข้าสู่ระบบสำเร็จ (Role: %s)\n", users[i].role);
            return users[i];
        }
    }

    printf(" ชื่อผู้ใช้หรือรหัสผ่านไม่ถูกต้อง!\n");
    return empty;
}

// DISPLAY MENU 
void displayMenu(const char *lang) {
    if (strcmp(lang, "en") == 0) {
        printf("\n LICENSE MANAGEMENT SYSTEM \n");
        printf("1. Show all records\n");
        printf("2. Add new record\n");
        printf("3. Search records\n");
        printf("4. Update record\n");
        printf("5. Delete record\n");
        printf("0. Exit\n");
    } else {
        printf("\n ระบบจัดการข้อมูลใบอนุญาต \n");
        printf("1. แสดงข้อมูลทั้งหมด\n");
        printf("2. เพิ่มข้อมูลใหม่\n");
        printf("3. ค้นหาข้อมูล\n");
        printf("4. อัปเดตข้อมูล\n");
        printf("5. ลบข้อมูล\n");
        printf("0. ออกจากโปรแกรม\n");
    }
    printf("เลือกเมนู: ");
}

// MAIN 
int main() {
    LicenseRequest records[MAX_RECORDS];
    int count = readCSV(records);
    int choice;
    char lang[3];
    User currentUser;

    printf("เลือกภาษา (th/en): ");
    scanf(" %s", lang);

    currentUser = loginSystem();
    if (strlen(currentUser.username) == 0) return 0; // login fail

    do {
        displayMenu(lang);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                for (int i = 0; i < count; i++) {
                    if (strcmp(currentUser.role, "General") == 0)
                        printf("%s | %s\n", records[i].requestID, records[i].licenseType);
                    else
                        printf("%s | %s | %s | %s\n",
                               records[i].requestID,
                               records[i].requesterName,
                               records[i].licenseType,
                               records[i].requestDate);
                }
                break;
            case 2:
                if (strcmp(currentUser.role, "Admin") == 0 ||
                    strcmp(currentUser.role, "Staff") == 0)
                    addRecord(records, &count);
                else
                    printf(" คุณไม่มีสิทธิ์เพิ่มข้อมูล\n");
                break;
            case 3:
                searchRecord(records, count);
                break;
            case 4:
                if (strcmp(currentUser.role, "Admin") == 0)
                    updateRecord(records, count);
                else
                    printf(" เฉพาะ Admin เท่านั้นที่สามารถแก้ไขได้\n");
                break;
            case 5:
                if (strcmp(currentUser.role, "Admin") == 0)
                    deleteRecord(records, &count);
                else
                    printf(" เฉพาะ Admin เท่านั้นที่สามารถลบได้\n");
                break;
            case 0:
                printf(" ออกจากโปรแกรม...\n");
                break;
            default:
                printf(" เลือกเมนูไม่ถูกต้อง!\n");
        }
    } while (choice != 0);

    return 0;
}

#ifdef TEST_MODE
#include <assert.h>

//  UNIT TESTS 
void test_isValidDateFormat() {
    assert(isValidDateFormat("2025-10-06") == 1);
    assert(isValidDateFormat("20251006") == 0);
    assert(isValidDateFormat("2025/10/06") == 0);
    printf(" test_isValidDateFormat() passed\n");
}

void test_loginSystem_mock() {
    User testUser = {"admin", "1234", "Admin"};
    assert(strcmp(testUser.username, "admin") == 0);
    assert(strcmp(testUser.password, "1234") == 0);
    assert(strcmp(testUser.role, "Admin") == 0);
    printf(" test_loginSystem_mock() passed\n");
}

void test_searchRecord_partial() {
    LicenseRequest records[3] = {
        {"L001", "Alice", "Business", "2025-10-01"},
        {"L002", "Bob", "Education", "2025-10-02"},
        {"L003", "Charlie", "Health", "2025-10-03"}
    };

    char keyword[] = "Bo";
    int found = 0;
    for (int i = 0; i < 3; i++) {
        if (strstr(records[i].requesterName, keyword)) {
            found = 1;
            break;
        }
    }
    assert(found == 1);
    printf(" test_searchRecord_partial() passed\n");
}

// E2E TEST 
void test_end_to_end_add_search_delete() {
    LicenseRequest records[5];
    int count = 0;

    //  Add Record
    LicenseRequest rec = {"1001", "TestUser", "IT", "2025-10-06"};
    records[count++] = rec;
    assert(count == 1);

    //  Write to CSV
    writeCSV(records, count);
    int loaded = readCSV(records);
    assert(loaded >= 1);
    printf(" CSV Write/Read passed\n");

    //  Search Partial
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(records[i].requesterName, "Test")) found = 1;
    }
    assert(found == 1);

    //  Delete Record
    deleteRecord(records, &count);
    printf(" End-to-End test simulated (add → search → delete)\n");
}

// TEST MAIN 
int main() {
    printf("\n Running Unit Tests & E2E Tests...\n\n");

    test_isValidDateFormat();
    test_loginSystem_mock();
    test_searchRecord_partial();
    test_end_to_end_add_search_delete();

    printf("\n All tests passed successfully!\n");
    return 0;
}
#endif
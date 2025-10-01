#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256       
#define MAX_RECORDS 1000   
#define FILE_NAME "data.csv" 

// โครงสร้างเก็บข้อมูลการขอใบอนุญาต
typedef struct {
    char requestID[20];     
    char requesterName[50];   
    char licenseType[50];   
    char requestDate[20];   
    } LicenseRequest;

// อ่านข้อมูลจากไฟล์ CSV
int readCSV(LicenseRequest records[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf(" ไม่พบไฟล์ %s\n", FILE_NAME);
        return 0;
    }
    char line[MAX_LINE];
    int count = 0;

    // Header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, " %19[^,],%49[^,],%19[^,],%49[^\n]",
               records[count].requestID,
               records[count].requesterName,
               records[count].licenseType,
               records[count].requestDate);
        count++;
    }

    fclose(file);
    return count;
}

// เขียนข้อมูลทั้งหมดลงไฟล์ CSV
void writeCSV(LicenseRequest records[], int count) {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("❌ ไม่สามารถเขียนไฟล์ได้\n");
        return;
    }

    // เขียน Header
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
// เพิ่มข้อมูลใหม่ 
void addRecord(LicenseRequest records[], int *count) {
    LicenseRequest newRec;

    printf("หมายเลขคำขอ: ");
    scanf(" %[^\n]", newRec.requestID);
    printf("ชื่อผู้ขอ: ");
    scanf(" %[^\n]", newRec.requesterName);
    printf("ประเภทใบอนุญาต: ");
    scanf(" %[^\n]", newRec.licenseType);
    printf("วันที่ขอ (YYYY-MM-DD): ");
    scanf(" %[^\n]", newRec.requestDate);

    records[*count] = newRec;
    (*count)++;

    writeCSV(records, *count);
    printf("  เพิ่มข้อมูลเรียบร้อย!\n");
}
// ค้นหาข้อมูล 
void searchRecord(LicenseRequest records[], int count) {
    char keyword[50];
    int found = 0;

    printf("กรอกหมายเลขคำขอหรือชื่อผู้ขอที่ต้องการค้นหา: ");
    scanf(" %[^\n]", keyword);

    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].requestID, keyword) == 0 ||
            strcmp(records[i].requesterName, keyword) == 0) {
            printf("พบข้อมูล: %s | %s | %s | %s\n",
                   records[i].requestID,
                   records[i].requesterName,
                   records[i].licenseType,
                   records[i].requestDate);
            found = 1;
        }
    }
}

// อัปเดตข้อมูล 
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
            printf("  อัปเดตเรียบร้อย!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("  ไม่พบหมายเลขคำขอ\n");
    }
}

// ลบข้อมูล 
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
            printf("  ลบข้อมูลเรียบร้อย!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("  ไม่พบหมายเลขคำขอ\n");
    }
}

// แสดงเมนู
void displayMenu() {
    printf("\n ระบบจัดการข้อมูลการขอใบอนุญาต \n");
    printf("1. แสดงข้อมูลทั้งหมด\n");
    printf("2. เพิ่มข้อมูลใหม่ \n");
    printf("3. ค้นหาข้อมูล \n");
    printf("4. อัปเดตข้อมูล \n");
    printf("5. ลบข้อมูล \n");
    printf("0. ออกจากโปรแกรม\n");
    printf("เลือกเมนู: ");
}

// main program
int main() {
    LicenseRequest records[MAX_RECORDS];
    int count = readCSV(records);
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                for (int i = 0; i < count; i++) {
                    printf("%s | %s | %s | %s\n",
                           records[i].requestID,
                           records[i].requesterName,
                           records[i].licenseType,
                           records[i].requestDate);
                }
                break;
            case 2:
                addRecord(records, &count);
                break;
            case 3:
                searchRecord(records, count);
                break;
            case 4:
                updateRecord(records, count);
                break;
            case 5:
                deleteRecord(records, &count);
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

       
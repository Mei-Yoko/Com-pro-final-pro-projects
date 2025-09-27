#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256       // ขนาดบรรทัดสูงสุด
#define MAX_RECORDS 1000   // จำนวนข้อมูลสูงสุดที่เก็บได้
#define FILE_NAME "data.csv" // ชื่อไฟล์ CSV

// โครงสร้างเก็บข้อมูลการขอใบอนุญาต
typedef struct {
    char requestID[20];     // หมายเลขคำขอ
    char requesterName[50];   // ชื่อผู้ขอ
    char licenseType[50];   // ประเภทใบอนุญาต
    char requestDate[20];   // วันที่ขอ
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

    // ข้ามบรรทัดแรก (Header)
    fgets(line, sizeof(line), file);

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
//จบ
       
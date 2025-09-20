#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256       // ขนาดบรรทัดสูงสุด
#define MAX_RECORDS 1000   // จำนวนข้อมูลสูงสุดที่เก็บได้
#define FILE_NAME "license_requests.csv" // ชื่อไฟล์ CSV

// โครงสร้างเก็บข้อมูลการขอใบอนุญาต
typedef struct {
    char requestID[20];     // หมายเลขคำขอ
    char requestName[50];   // ชื่อผู้ขอ
    char licenseType[50];   // ประเภทใบอนุญาต
    char requestDate[20];   // วันที่ขอ
    } LicenseRequest;
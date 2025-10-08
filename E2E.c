#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("License Management System \n");

    //  input 
    FILE *f = fopen("testdata.csv", "w");
    if (!f) {
        printf(" ไม่สามารถสร้าง test_input.txt ได้\n");
        return 1;
    }

    fprintf(f,
        "th\n"             // เลือกภาษา
        "admin\n"           // username
        "1234\n"            // password
        "1\n"               // แสดงข้อมูล
        "2\n"               // เพิ่มข้อมูลใหม่
        "L000\n"          // Request ID
        "สมชาย เกิดใหม่\n" // Requester Name
        "Driving License\n"   // License Type
        "2025-10-06\n"      // Request Date
        "3\n"               // ค้นหา
        "L000\n"          // Keyword
        "4\n"               // อัปเดตข้อมูล
        "L000\n"          // Request ID
        "ใบขับขี่ทั่วไป\n"  // License Type ใหม่
        "5\n"               // ลบข้อมูล
        "L000\n"          // Request ID
        "0\n"               // ออกจากโปรแกรม
    );
    fclose(f);

    // บันทึก output
    int result = system("./license_system < testdata.csv > testdata.csv");

    if (result != 0) {
        printf(" โปรแกรมหลักรันไม่สำเร็จ (exit code %d)\n", result);
        return 1;
    }

    // ผลลัพธ์ที่
    FILE *out = fopen("testdata.csv", "r");
    if (!out) {
        printf(" ไม่พบ testdata.csv\n");
        return 1;
    }

    char buffer[10000];
    fread(buffer, 1, sizeof(buffer) - 1, out);
    fclose(out);
    buffer[sizeof(buffer) - 1] = '\0';

    // ตรวจสอบ
    int passed = 1;
    if (strstr(buffer, "เข้าสู่ระบบสำเร็จ") == NULL) { printf(" ไม่พบข้อความเข้าสู่ระบบสำเร็จ\n"); passed = 0; }
    if (strstr(buffer, "เพิ่มข้อมูลเรียบร้อย") == NULL) { printf(" ไม่พบข้อความเพิ่มข้อมูล\n"); passed = 0; }
    if (strstr(buffer, "พบข้อมูล") == NULL) { printf(" ไม่พบผลลัพธ์จากการค้นหา\n"); passed = 0; }
    if (strstr(buffer, "อัปเดตเรียบร้อย") == NULL) { printf(" ไม่พบข้อความอัปเดต\n"); passed = 0; }
    if (strstr(buffer, "ลบข้อมูลเรียบร้อย") == NULL) { printf(" ไม่พบข้อความลบข้อมูล\n"); passed = 0; }

    // แสดงผล
    printf("\n OUTPUT LOG \n");
    system("cat testdata.csv");

    printf("\n RESULT \n");
    if (passed)
        printf(" TEST PASSED\n");
    else
        printf(" TEST FAILED\n");

    return 0;
}

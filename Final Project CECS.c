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

// USERS 
User users[] = {
    {"admin", "1234", "Admin"},
    {"staff", "1234", "Staff"},
    {"user", "1234", "General"}
};

// HELPER: Clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// HELPER: Safe string input with length limit
int safeInput(char *buffer, int maxLen) {
    if (fgets(buffer, maxLen, stdin) == NULL) {
        return 0;
    }
    // Remove trailing newline
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
    return 1;
}

// HELPER: Trim whitespace
void trim(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

int isEmpty(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) return 0;
        str++;
    }
    return 1;
}

//  Date (YYYY-MM-DD)
int isValidDateFormat(const char *date) {
    if (strlen(date) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if ((i == 4 || i == 7) && date[i] != '-') return 0;
        if ((i != 4 && i != 7) && !isdigit(date[i])) return 0;
    }
    
   
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) return 0;
    
    //  ranges date
    if (year < 1900 || year > 2100) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    
    
    int daysInMonth[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day > daysInMonth[month - 1]) return 0;
    
    return 1;
}

//  Check  RequestID
int isDuplicateID(LicenseRequest records[], int count, const char *reqID) {
    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].requestID, reqID) == 0) {
            return 1;
        }
    }
    return 0;
}

// READ CSV 
int readCSV(LicenseRequest records[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("  ไม่พบไฟล์ %s (จะสร้างใหม่เมื่อเพิ่มข้อมูล)\n", FILE_NAME);
        return 0;
    }
    
    char line[MAX_LINE];
    int count = 0;
    int lineNum = 0;
    
    // Skip header
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return 0;
    }
    lineNum++;

    while (fgets(line, sizeof(line), file) && count < MAX_RECORDS) {
        lineNum++;
        
        //  size limits
        int parsed = sscanf(line, " %19[^,],%49[^,],%49[^,],%19[^\n]",
               records[count].requestID,
               records[count].requesterName,
               records[count].licenseType,
               records[count].requestDate);
        
        if (parsed == 4) {
            trim(records[count].requestID);
            trim(records[count].requesterName);
            trim(records[count].licenseType);
            trim(records[count].requestDate);
            
            if (!isEmpty(records[count].requestID)) {
                count++;
            }
        } else {
            printf("  บรรทัด %d มีรูปแบบไม่ถูกต้อง (ข้าม)\n", lineNum);
        }
    }
    
    fclose(file);
    printf("✓ โหลดข้อมูล %d รายการ\n", count);
    return count;
}

// WRITE CSV
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

// ADD RECORD 
void addRecord(LicenseRequest records[], int *count) {
    if (*count >= MAX_RECORDS) {
        printf(" ไม่สามารถเพิ่มข้อมูลได้ (เต็ม %d รายการ)\n", MAX_RECORDS);
        return;
    }
    
    LicenseRequest newRec;
    
    // Input RequestID
    do {
        printf("หมายเลขคำขอ: ");
        clearInputBuffer();
        if (!safeInput(newRec.requestID, sizeof(newRec.requestID))) {
            printf(" ข้อผิดพลาดในการรับข้อมูล\n");
            return;
        }
        trim(newRec.requestID);
        
        if (isEmpty(newRec.requestID)) {
            printf(" หมายเลขคำขอต้องไม่ว่าง!\n");
            continue;
        }
        
        if (isDuplicateID(records, *count, newRec.requestID)) {
            printf(" หมายเลขคำขอซ้ำ! กรุณาใช้หมายเลขอื่น\n");
            continue;
        }
        break;
    } while (1);
    
    // Input RequesterName
    do {
        printf("ชื่อผู้ขอ: ");
        if (!safeInput(newRec.requesterName, sizeof(newRec.requesterName))) {
            printf(" ข้อผิดพลาดในการรับข้อมูล\n");
            return;
        }
        trim(newRec.requesterName);
        
        if (isEmpty(newRec.requesterName)) {
            printf(" ชื่อผู้ขอต้องไม่ว่าง!\n");
            continue;
        }
        break;
    } while (1);
    
    // Input LicenseType
    do {
        printf("ประเภทใบอนุญาต: ");
        if (!safeInput(newRec.licenseType, sizeof(newRec.licenseType))) {
            printf(" ข้อผิดพลาดในการรับข้อมูล\n");
            return;
        }
        trim(newRec.licenseType);
        
        if (isEmpty(newRec.licenseType)) {
            printf(" ประเภทใบอนุญาตต้องไม่ว่าง!\n");
            continue;
        }
        break;
    } while (1);
    
    // Input RequestDate
    do {
        printf("วันที่ขอ (YYYY-MM-DD): ");
        if (!safeInput(newRec.requestDate, sizeof(newRec.requestDate))) {
            printf(" ข้อผิดพลาดในการรับข้อมูล\n");
            return;
        }
        trim(newRec.requestDate);
        
        if (!isValidDateFormat(newRec.requestDate)) {
            printf(" รูปแบบวันที่ไม่ถูกต้อง! (ต้องเป็น YYYY-MM-DD เช่น 2025-10-06)\n");
            continue;
        }
        break;
    } while (1);

    records[*count] = newRec;
    (*count)++;
    writeCSV(records, *count);
    printf("✓ เพิ่มข้อมูลเรียบร้อย!\n");
}

// SEARCH RECORD
void searchRecord(LicenseRequest records[], int count) {
    char keyword[50];
    int found = 0;

    printf("กรอกคำค้นหา (ชื่อบางส่วนหรือหมายเลขคำขอ): ");
    clearInputBuffer();
    if (!safeInput(keyword, sizeof(keyword))) {
        printf(" ข้อผิดพลาดในการรับข้อมูล\n");
        return;
    }
    trim(keyword);

    if (isEmpty(keyword)) {
        printf("⚠️  กรุณากรอกคำค้นหา\n");
        return;
    }

    printf("\n--- ผลการค้นหา ---\n");
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
        printf("ไม่พบข้อมูลที่ค้นหา\n");
}

// UPDATE RECORD
void updateRecord(LicenseRequest records[], int count) {
    char reqID[20];
    int found = 0;

    printf("กรอกหมายเลขคำขอที่ต้องการแก้ไข: ");
    clearInputBuffer();
    if (!safeInput(reqID, sizeof(reqID))) {
        printf(" ข้อผิดพลาดในการรับข้อมูล\n");
        return;
    }
    trim(reqID);

    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].requestID, reqID) == 0) {
            printf("\nข้อมูลเดิม:\n");
            printf("  หมายเลขคำขอ: %s\n", records[i].requestID);
            printf("  ชื่อผู้ขอ: %s\n", records[i].requesterName);
            printf("  ประเภทใบอนุญาต: %s\n", records[i].licenseType);
            printf("  วันที่ขอ: %s\n", records[i].requestDate);
            
            do {
                printf("\nประเภทใบอนุญาตใหม่: ");
                if (!safeInput(records[i].licenseType, sizeof(records[i].licenseType))) {
                    printf(" ข้อผิดพลาดในการรับข้อมูล\n");
                    return;
                }
                trim(records[i].licenseType);
                
                if (isEmpty(records[i].licenseType)) {
                    printf(" ประเภทใบอนุญาตต้องไม่ว่าง!\n");
                    continue;
                }
                break;
            } while (1);
            
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
    char confirm[10];
    int found = 0;

    printf("กรอกหมายเลขคำขอที่ต้องการลบ: ");
    clearInputBuffer();
    if (!safeInput(reqID, sizeof(reqID))) {
        printf(" ข้อผิดพลาดในการรับข้อมูล\n");
        return;
    }
    trim(reqID);

    for (int i = 0; i < *count; i++) {
        if (strcmp(records[i].requestID, reqID) == 0) {
            printf("\nข้อมูลที่จะลบ:\n");
            printf("  %s | %s | %s | %s\n",
                   records[i].requestID,
                   records[i].requesterName,
                   records[i].licenseType,
                   records[i].requestDate);
            
            printf("\nยืนยันการลบ? (yes/no): ");
            if (!safeInput(confirm, sizeof(confirm))) {
                printf(" ยกเลิกการลบ\n");
                return;
            }
            trim(confirm);
            
            if (strcmp(confirm, "yes") != 0 && strcmp(confirm, "YES") != 0) {
                printf(" ยกเลิกการลบ\n");
                return;
            }
            
            // erase records
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

// LOGIN SYSTEM
User loginSystem() {
    char username[20], password[20];
    User empty = {"", "", ""};

    printf("\n=== เข้าสู่ระบบ ===\n");
    printf("ชื่อผู้ใช้: ");
    if (scanf("%19s", username) != 1) {
        clearInputBuffer();
        printf(" ข้อผิดพลาดในการรับข้อมูล\n");
        return empty;
    }
    
    printf("รหัสผ่าน: ");
    if (scanf("%19s", password) != 1) {
        clearInputBuffer();
        printf(" ข้อผิดพลาดในการรับข้อมูล\n");
        return empty;
    }

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
    if (scanf("%2s", lang) != 1) {
        printf(" ข้อผิดพลาด\n");
        return 1;
    }

    currentUser = loginSystem();
    if (strlen(currentUser.username) == 0) return 0;

    do {
        displayMenu(lang);
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf(" กรุณากรอกตัวเลข!\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("\n รายการข้อมูลทั้งหมด \n");
                if (count == 0) {
                    printf("(ยังไม่มีข้อมูล)\n");
                } else {
                    for (int i = 0; i < count; i++) {
                        if (strcmp(currentUser.role, "General") == 0)
                            printf("%d. %s | %s\n", i+1, records[i].requestID, records[i].licenseType);
                        else
                            printf("%d. %s | %s | %s | %s\n", i+1,
                                   records[i].requestID,
                                   records[i].requesterName,
                                   records[i].licenseType,
                                   records[i].requestDate);
                    }
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
                printf("✓ ออกจากโปรแกรม...\n");
                break;
            default:
                printf(" เลือกเมนูไม่ถูกต้อง!\n");
        }
    } while (choice != 0);

    return 0;
}


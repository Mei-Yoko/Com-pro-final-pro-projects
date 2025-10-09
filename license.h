
#ifndef LICENSE_MANAGEMENT_H
#define LICENSE_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 256
#define MAX_RECORDS 1000
#define FILE_NAME "data.csv"

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


void clearInputBuffer();
int safeInput(char *buffer, int maxLen);
void trim(char *str);
int isEmpty(const char *str);

int isValidDateFormat(const char *date);
int isDuplicateID(LicenseRequest records[], int count, const char *reqID);


int readCSV(LicenseRequest records[]);
void writeCSV(LicenseRequest records[], int count);

void addRecord(LicenseRequest records[], int *count);
void searchRecord(LicenseRequest records[], int count);
void updateRecord(LicenseRequest records[], int count);
void deleteRecord(LicenseRequest records[], int *count);

User loginSystem();

void displayMenu(const char *lang);


int main();

int run_unit_tests(void);
int run_e2e_tests(void);

#endif
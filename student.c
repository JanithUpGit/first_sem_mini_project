// student.c
#include <stdio.h>
#include <string.h>
#include "structs.h"

void addStudent() {
    FILE *fp = fopen("students.txt", "a");
    Student s;
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Registration Number: ");
    scanf(" %[^\n]", s.regNo);
    printf("Enter Contact Number: ");
    scanf(" %[^\n]", s.contact);
    printf("Enter Room Number: ");
    scanf(" %[^\n]", s.room);
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student Added Successfully.\n");
}

void viewStudents() {
    FILE *fp = fopen("students.txt", "r");
    Student s;
    printf("\n--- Student List ---\n");
    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("Name: %s\nReg No: %s\nContact: %s\nRoom: %s\n\n", s.name, s.regNo, s.contact, s.room);
    }
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.txt", "r");
    Student s;
    char reg[MAX];
    int found = 0;
    printf("Enter Registration Number to search: ");
    scanf(" %[^\n]", reg);
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (strcmp(s.regNo, reg) == 0) {
            printf("\nStudent Found:\n");
            printf("Name: %s\nReg No: %s\nContact: %s\nRoom: %s\n", s.name, s.regNo, s.contact, s.room);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student Not Found.\n");
    }
    fclose(fp);
}

void updateContact() {
    FILE *fp = fopen("students.txt", "r+");
    Student s;
    char reg[MAX];
    printf("Enter Registration Number to update contact: ");
    scanf(" %[^\n]", reg);
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (strcmp(s.regNo, reg) == 0) {
            printf("Enter New Contact Number: ");
            scanf(" %[^\n]", s.contact);
            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            printf("Contact Updated Successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student Not Found.\n");
    }
    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Student s;
    char reg[MAX];
    printf("Enter Registration Number to delete: ");
    scanf(" %[^\n]", reg);
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (strcmp(s.regNo, reg) != 0) {
            fwrite(&s, sizeof(Student), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        printf("Student Deleted Successfully.\n");
    } else {
        printf("Student Not Found.\n");
    }
}

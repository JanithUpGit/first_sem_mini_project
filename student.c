// student.c
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include <time.h>

void addStudent() {
    Student student;

    FILE *file = fopen("students.dat", "ab");
    if (file == NULL) {
        printf("Error opening student database file!\n");
        return;
    }

    printf("Student Admission Form\n");
    printf("===========================\n\n");

    printf("Enter ID: ");
    scanf("%d", &student.tgNo);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter Name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = 0; // Remove newline

    printf("Enter Gender: ");
    fgets(student.gender, sizeof(student.gender), stdin);
    student.gender[strcspn(student.gender, "\n")] = 0;

    printf("Enter Room Number: ");
    scanf("%d", &student.room);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter Phone: ");
    fgets(student.contact, sizeof(student.contact), stdin);
    student.contact[strcspn(student.contact, "\n")] = 0;

    fwrite(&student, sizeof(Student), 1, file);
    fclose(file);

    printf("\nStudent added successfully!\n");
    printf("===========================\n");
}


void viewStudents()
{
    FILE *fp = fopen("students.dat", "r");
    Student s;

    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("\n--- Student List ---\n\n");
    while (fread(&s, sizeof(Student), 1, fp))
    {
        printf("Name: %s\nTgNo: Tg %d\nContact: %s\nRoom: %d\nGender %s \n\n\n", s.name, s.tgNo, s.contact, s.room, s.gender);
    }

    fclose(fp);
}


void searchStudent() {
    FILE *fp = fopen("students.dat", "r");
    Student s;
    int tg ;
    int found = 0;
    printf("Enter Tg Number to search: ");
    scanf(" %d", &tg);getchar();
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.tgNo == tg) {
            printf("\nStudent Found:\n");
            printf("Name: %s\nTgNo: Tg %d\nContact: %s\nRoom: %d\nGender %s \n", s.name, s.tgNo, s.contact, s.room, s.gender);
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
    FILE *fp = fopen("students.dat", "r+");
    Student s;
    int tg;
    printf("Enter Registration Number to update contact: ");
    scanf(" %d", &tg);getchar();
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.tgNo == tg) {

            printf("Enter New Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;
        
            printf("Enter New Gender: ");
            fgets(s.gender, sizeof(s.gender), stdin);
            s.gender[strcspn(s.gender, "\n")] = 0;
        
            printf("Enter New Room Number: ");
            scanf("%d", &s.room);
            getchar();
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
    FILE *fp = fopen("students.dat", "r");
    FILE *temp = fopen("temp.dat", "w");
    Student s;
    int tg;
    printf("Enter Registration Number to delete: ");
    scanf(" %d", &tg);
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.tgNo == tg) {
            fwrite(&s, sizeof(Student), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.txt", "students.dat");

    if (found) {
        printf("Student Deleted Successfully.\n");
    } else {
        printf("Student Not Found.\n");
    }
}

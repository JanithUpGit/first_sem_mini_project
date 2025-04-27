
#include <stdio.h>
#include <string.h>
#include "structs.h"

char rooms[][MAX] = {"101", "102", "103", "104", "201", "202", "203", "204"};
int totalRooms = 8;

void assignRoom() {
    FILE *fp = fopen("students.txt", "r+");
    Student s;
    char reg[MAX];
    printf("Enter Registration Number to assign room: ");
    scanf(" %[^\n]", reg);
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (strcmp(s.regNo, reg) == 0) {
            printf("Enter New Room Number: ");
            scanf(" %[^\n]", s.room);
            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            printf("Room Assigned Successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student Not Found.\n");
    }
    fclose(fp);
}

void viewAvailableRooms() {
    int occupied[8] = {0};
    FILE *fp = fopen("students.txt", "r");
    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        for (int i = 0; i < totalRooms; i++) {
            if (strcmp(rooms[i], s.room) == 0) {
                occupied[i] = 1;
            }
        }
    }
    fclose(fp);
    printf("\n--- Available Rooms ---\n");
    for (int i = 0; i < totalRooms; i++) {
        if (occupied[i] == 0) {
            printf("Room %s\n", rooms[i]);
        }
    }
}

void checkRoomOccupancy() {
    int count[8] = {0};
    FILE *fp = fopen("students.txt", "r");
    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        for (int i = 0; i < totalRooms; i++) {
            if (strcmp(rooms[i], s.room) == 0) {
                count[i]++;
            }
        }
    }
    fclose(fp);
    printf("\n--- Room Occupancy ---\n");
    for (int i = 0; i < totalRooms; i++) {
        printf("Room %s: %d Student(s)\n", rooms[i], count[i]);
    }
}

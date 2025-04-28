#include <stdio.h>
#include <string.h>
#include "structs.h"

#define NUMBER_OF_ROOMS 200

void viewAvailableRooms() {
    FILE *fp = fopen("students.dat", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Student s;
    int roomCounts[NUMBER_OF_ROOMS] = {0};

    
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.room >= 0 && s.room < NUMBER_OF_ROOMS) {
            roomCounts[s.room]++;
        }
    }
    fclose(fp);

    printf("\n--- Available Rooms ---\n");
    for (int i = 0; i < NUMBER_OF_ROOMS; i++) {
        if (roomCounts[i] < 4) { 
            printf("Room %d - %d spaces available\n", i, 4 - roomCounts[i]);
        }
    }
}

void checkRoomOccupancy() {
    FILE *fp = fopen("students.dat", "rb"); // binary read
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Student students[1000]; 
    int studentCount = 0;

    
    while (fread(&students[studentCount], sizeof(Student), 1, fp)) {
        studentCount++;
    }
    fclose(fp);

    printf("\n--- Room Occupancy ---\n");

    for (int room = 0; room < NUMBER_OF_ROOMS; room++) {
        int roomStudentCount = 0;
        
        
        for (int i = 0; i < studentCount; i++) {
            if (students[i].room == room) {
                if (roomStudentCount == 0) {
                    printf("\nRoom %d:\n", room);
                }
                printf("  TgNo: %d, Name: %s\n", students[i].tgNo, students[i].name);
                roomStudentCount++;
            }
        }
        
        if (roomStudentCount == 0) {
            // Room is empty
            // Optional: Uncomment below if you want to print empty rooms
            // printf("\nRoom %d: Empty\n", room);
        }
    }
}

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
    int roomCounts[NUMBER_OF_ROOMS] = {0}; // array to store number of students in each room

    // Read all students and count
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.room >= 0 && s.room < NUMBER_OF_ROOMS) {
            roomCounts[s.room]++;
        }
    }
    fclose(fp);

    printf("\n--- Available Rooms ---\n");
    for (int i = 0; i < NUMBER_OF_ROOMS; i++) {
        if (roomCounts[i] < 4) { // room is available
            printf("Room %d - %d spaces available\n", i, 4 - roomCounts[i]);
        }
    }
}

void checkRoomOccupancy() {
    FILE *fp = fopen("students.dat", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Student s;
    int roomCounts[NUMBER_OF_ROOMS] = {0};

    // Read all students and count
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.room >= 0 && s.room < NUMBER_OF_ROOMS) {
            roomCounts[s.room]++;
        }
    }
    fclose(fp);

    printf("\n--- Room Occupancy ---\n");
    for (int i = 0; i < NUMBER_OF_ROOMS; i++) {
        printf("Room %d - %d students\n", i, roomCounts[i]);
    }
}

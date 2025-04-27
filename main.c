// main.c
#include <stdio.h>
#include "student.h"
#include "room.h"

int main() {
    int choice;
    printf("\n=== Welcome to Uor Fot Hostel Management System ===\n");
    while (1) {
        
        printf("\n=== Manin Menu ===\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Contact\n");
        printf("5. Delete Student\n");
        printf("6. Assign Room\n");
        printf("7. View Available Rooms\n");
        printf("8. Check Room Occupancy\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateContact(); break;
            case 5: deleteStudent(); break;
            case 6: assignRoom(); break;
            case 7: viewAvailableRooms(); break;
            case 8: checkRoomOccupancy(); break;
            case 9: return 0;
            default: printf("Invalid choice. Try again!\n");
        }
    }
}

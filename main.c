#include "movie_system.h"
#include <stdio.h>
#include <stdio.h>

int main() {
    initializeMovies();
    loadUserData();
    loadMovieData();
    loadEarningsData();
    
    printf("Welcome to the Movie Ticket Booking System!\n");
    while (1) {
        printf("\nMain Interface:\n");
        printf("1. User Interface\n");
        printf("2. Admin Interface\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: mainMenu(); break;
            case 2: adminMenu(); break;
            case 3: saveEarningsData(); return 0;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

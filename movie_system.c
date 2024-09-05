#include <stdio.h>
#include <string.h>

#define MAX_MOVIES 100
#define MAX_BOOKINGS 50
#define MAX_USERS 10
#define MAX_SEATS 30
#define SEATS_PER_ROW 10 

// Data Structures
typedef struct {
    int id;
    char name[50];
    char time[10];
    int availableSeats;
    int pricePerSeat;
    float rating;
    char reviews[5][100];
    int reviewCount;
    int seatLayout[MAX_SEATS];
} Movie;

typedef struct {
    int bookingId;
    char customerName[50];
    int movieId;
    int seatsBooked[MAX_SEATS];
    int totalPrice;
} Booking;

typedef struct {
    char username[50];
    char password[20];
    Booking bookings[MAX_BOOKINGS];
    int bookingCount;
    int loyaltyPoints;
    char email[50];
    char phone[15];
} User;

Movie movies[MAX_MOVIES];
User users[MAX_USERS];
Booking bookings[MAX_BOOKINGS];
int userCount = 0;
int totalEarnings = 0;
int bookingCount = 0;
User *loggedInUser = NULL;

void initializeMovies() {
    strcpy(movies[0].name, "Avengers: Endgame");
    strcpy(movies[0].time, "12:00 PM");
    movies[0].id = 1;
    movies[0].availableSeats = 30;
    movies[0].pricePerSeat = 10;
    movies[0].rating = 4.5;
    movies[0].reviewCount = 0;
    memset(movies[0].seatLayout, 0, sizeof(movies[0].seatLayout));

    strcpy(movies[1].name, "Inception");
    strcpy(movies[1].time, "3:00 PM");
    movies[1].id = 2;
    movies[1].availableSeats = 20;
    movies[1].pricePerSeat = 12;
    movies[1].rating = 4.7;
    movies[1].reviewCount = 0;
    memset(movies[1].seatLayout, 0, sizeof(movies[1].seatLayout));

    strcpy(movies[2].name, "Interstellar");
    strcpy(movies[2].time, "6:00 PM");
    movies[2].id = 3;
    movies[2].availableSeats = 25;
    movies[2].pricePerSeat = 15;
    movies[2].rating = 4.8;
    movies[2].reviewCount = 0;
    memset(movies[2].seatLayout, 0, sizeof(movies[2].seatLayout));

    strcpy(movies[3].name, "The Dark Knight");
    strcpy(movies[3].time, "9:00 PM");
    movies[3].id = 4;
    movies[3].availableSeats = 15;
    movies[3].pricePerSeat = 8;
    movies[3].rating = 4.9;
    movies[3].reviewCount = 0;
    memset(movies[3].seatLayout, 0, sizeof(movies[3].seatLayout));

    strcpy(movies[4].name, "Titanic");
    strcpy(movies[4].time, "11:00 PM");
    movies[4].id = 5;
    movies[4].availableSeats = 10;
    movies[4].pricePerSeat = 10;
    movies[4].rating = 4.6;
    movies[4].reviewCount = 0;
    memset(movies[4].seatLayout, 0, sizeof(movies[4].seatLayout));
}

void displayMovies() {
    printf("\n=========================================\n");
    printf("                Available Movies\n");
    printf("=========================================\n");
    for (int i = 0; i < MAX_MOVIES; i++) {
        if (movies[i].id != 0) {
            printf("%d. %s (%s) - Available Seats: %d | Price: $%d | Rating: %.1f/5\n",
                   movies[i].id, movies[i].name, movies[i].time,
                   movies[i].availableSeats, movies[i].pricePerSeat, movies[i].rating);
        }
    }
    printf("=========================================\n");
}

void searchMovie() {
    char searchName[50];
    printf("Enter the movie name to search: ");
    scanf(" %[^\n]%*c", searchName);
    printf("\nSearch Results:\n");
    int found = 0;
    for (int i = 0; i < MAX_MOVIES; i++) {
        if (movies[i].id != 0 && strstr(movies[i].name, searchName) != NULL) {
            printf("%d. %s (%s) - Available Seats: %d | Price: $%d | Rating: %.1f/5\n",
                   movies[i].id, movies[i].name, movies[i].time,
                   movies[i].availableSeats, movies[i].pricePerSeat, movies[i].rating);
            found = 1;
        }
    }
    if (!found) {
        printf("No movies found with the name '%s'.\n", searchName);
    }
}

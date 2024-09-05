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

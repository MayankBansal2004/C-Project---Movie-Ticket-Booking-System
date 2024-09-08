#include <stdio.h>
#include <string.h>
#include "movie_system.h"
#include <Windows.h>

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

Movie movies[MAX_MOVIES] = {0};
User users[MAX_USERS] = {0};
Booking bookings[MAX_BOOKINGS] = {0};
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

void bookTicket() {
    if (loggedInUser == NULL) {
        printf("\nPlease log in to book tickets.\n");
        return;
    }

    char customerName[50];
    int movieChoice;
    printf("\nEnter your name: ");
    scanf("%s", customerName);
    displayMovies();
    printf("\nEnter the Movie ID you want to book: ");
    scanf("%d", &movieChoice);

    if (movieChoice < 1 || movieChoice > MAX_MOVIES || movies[movieChoice - 1].id == 0) {
        printf("Invalid Movie ID!\n");
        return;
    }

    int seatsBooked[MAX_SEATS] = {0}; // Initialize to 0
    seatSelection(movieChoice, seatsBooked);

    int totalPrice = 0;
    for (int i = 0; i < MAX_SEATS; i++) {
        if (seatsBooked[i] == 1) {  // Check for booked seats
            totalPrice += movies[movieChoice - 1].pricePerSeat;
        }
    }

    applyDiscount(&totalPrice);
    paymentProcessing(&totalPrice);
    
    bookings[bookingCount].bookingId = bookingCount + 1;
    strcpy(bookings[bookingCount].customerName, customerName);
    bookings[bookingCount].movieId = movieChoice;
    memcpy(bookings[bookingCount].seatsBooked, seatsBooked, sizeof(seatsBooked));
    bookings[bookingCount].totalPrice = totalPrice;
    
    loggedInUser->bookings[loggedInUser->bookingCount++] = bookings[bookingCount];
    bookingCount++;
    loggedInUser->loyaltyPoints += totalPrice / 10; // Earn points (1 point per $10 spent)
    
    printf("Booking successful! Your booking ID is %d\n", bookings[bookingCount - 1].bookingId);
    printf("Total price: $%d\n", totalPrice);
    printf("Loyalty points earned: %d\n", totalPrice / 10);
}

void viewBookings() {
    if (loggedInUser == NULL) {
        printf("\nPlease log in to view your bookings.\n");
        return;
    }

    if (loggedInUser->bookingCount == 0) {
        printf("\nNo bookings made yet.\n");
        return;
    }

    printf("\nYour Booking History:\n");
    for (int i = 0; i < loggedInUser->bookingCount; i++) {
        printf("Booking ID: %d | Movie: %s | Seats: ",
               loggedInUser->bookings[i].bookingId,
               movies[loggedInUser->bookings[i].movieId - 1].name);
        for (int j = 0; j < MAX_SEATS; j++) {
            if (loggedInUser->bookings[i].seatsBooked[j]) {
                printf("%d ", j + 1);
            }
        }
        printf("| Total Price: $%d\n", loggedInUser->bookings[i].totalPrice);
    }
}

void cancelBooking() {
    if (loggedInUser == NULL) {
        printf("\nPlease log in to cancel bookings.\n");
        return;
    }

    int bookingId;
    printf("\nEnter the booking ID to cancel: ");
    scanf("%d", &bookingId);
    int found = 0;

    for (int i = 0; i < loggedInUser->bookingCount; i++) {
        if (loggedInUser->bookings[i].bookingId == bookingId) {
            found = 1;
            
            // Update available seats in the movie
            int movieId = loggedInUser->bookings[i].movieId;
            for (int j = 0; j < MAX_SEATS; j++) {
                if (loggedInUser->bookings[i].seatsBooked[j]) {
                    movies[movieId - 1].seatLayout[j] = 0;  // Mark seat as available
                    movies[movieId - 1].availableSeats++;
                }
            }

            // Shift bookings to remove the canceled one
            for (int j = i; j < loggedInUser->bookingCount - 1; j++) {
                loggedInUser->bookings[j] = loggedInUser->bookings[j + 1];
            }
            loggedInUser->bookingCount--;
            bookingCount--;
            printf("Booking ID %d has been canceled.\n", bookingId);
            break;
        }
    }
    if (!found) {
        printf("Booking ID %d not found.\n", bookingId);
    }
}

void addMovie() {
    char name[50], time[10];
    int seats, price;
    float rating;

    printf("\nEnter Movie Name: ");
    scanf(" %[^\n]%*c", name);
    printf("Enter Movie Time (e.g., 12:00 PM): ");
    scanf("%[^\n]%*c", time);
    printf("Enter Number of Available Seats: ");
    scanf("%d", &seats);
    printf("Enter Price Per Seat: ");
    scanf("%d", &price);
    printf("Enter Movie Rating (0.0 to 5.0): ");
    scanf("%f", &rating);

    for (int i = 0; i < MAX_MOVIES; i++) {
        if (movies[i].id == 0) { // Find an empty slot
            movies[i].id = i + 1;
            strcpy(movies[i].name, name);
            strcpy(movies[i].time, time);
            movies[i].availableSeats = seats;
            movies[i].pricePerSeat = price;
            movies[i].rating = rating;
            movies[i].reviewCount = 0;
            memset(movies[i].seatLayout, 0, sizeof(movies[i].seatLayout));
            printf("Movie added successfully!\n");
            saveMovieData(); // Save the updated movie list
            return;
        }
    }

    printf("Movie list is full. Unable to add more movies.\n");
}

void removeMovie() {
    int movieId;
    printf("\nEnter the Movie ID to remove: ");
    scanf("%d", &movieId);

    if (movieId < 1 || movieId > MAX_MOVIES || movies[movieId - 1].id == 0) {
        printf("Invalid Movie ID!\n");
        return;
    }

    movies[movieId - 1].id = 0; // Mark movie as removed
    printf("Movie ID %d has been removed.\n", movieId);
    saveMovieData(); // Save the updated movie list
}

void saveMovieData() {
    FILE *file = fopen("movies.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(movies, sizeof(Movie), MAX_MOVIES, file);
    fclose(file);
    printf("Movie data saved successfully.\n");
}

void loadMovieData() {
    FILE *file = fopen("movies.dat", "rb");
    if (file == NULL) {
        // File doesn't exist, initialize with default movies or an empty list
        initializeMovies();
        return;
    }
    fread(movies, sizeof(Movie), MAX_MOVIES, file);
    fclose(file);
    printf("Movie data loaded successfully.\n");
}

void addReview(int movieId) {
    if (loggedInUser == NULL) {
        printf("\nPlease log in to add a review.\n");
        return;
    }

    if (movies[movieId - 1].reviewCount < 5) {
        printf("Enter your review: ");
        scanf(" %[^\n]%*c", movies[movieId - 1].reviews[movies[movieId - 1].reviewCount]);
        movies[movieId - 1].reviewCount++;
        printf("Review added successfully!\n");
    } else {
        printf("Review limit reached for this movie.\n");
    }
}

void displaySeatLayout(int movieId) {
    if (movieId < 1 || movieId > MAX_MOVIES || movies[movieId - 1].id == 0) {
        printf("Invalid Movie ID!\n");
        return;
    }

    printf("Seat Layout for '%s':\n", movies[movieId - 1].name);
    int rowCount = MAX_SEATS / SEATS_PER_ROW;

    for (int row = 0; row < rowCount; row++) {
        printf("Row %d: ", row + 1);
        for (int col = 0; col < SEATS_PER_ROW; col++) {
            int seatIndex = row * SEATS_PER_ROW + col;
            printf("%c ", movies[movieId - 1].seatLayout[seatIndex] ? 'X' : 'O');
        }
        printf("\n");
    }
    
    printf("Legend:\n");
    printf("O = Available\n");
    printf("X = Booked\n");
}

void seatSelection(int movieId, int *seatsBooked) {
    displaySeatLayout(movieId);

    int seatCount;
    printf("Enter the number of seats you want to book: ");
    scanf("%d", &seatCount);

    // Ensure seatCount doesn't exceed available seats
    if (seatCount > movies[movieId - 1].availableSeats) {
        printf("Not enough available seats. Please try again.\n");
        return;
    }

    for (int i = 0; i < seatCount; i++) {
        int seatNum;
        printf("Enter seat number %d: ", i + 1);
        scanf("%d", &seatNum);

        if (seatNum < 1 || seatNum > MAX_SEATS || movies[movieId - 1].seatLayout[seatNum - 1] == 1) {
            printf("Invalid or already booked seat number! Try again.\n");
            i--; // Re-enter the same seat number
            continue;
        }

        seatsBooked[seatNum - 1] = 1; // Mark the seat as booked in the user's selection
        movies[movieId - 1].seatLayout[seatNum - 1] = 'X'; // Mark the seat as booked in the movie's layout
        movies[movieId - 1].availableSeats--; // Decrease the count of available seats
    }
}

void applyDiscount(int *totalPrice) {
    if (loggedInUser->loyaltyPoints >= 50) {
        printf("You have %d loyalty points. Apply 10%% discount? (y/n): ", loggedInUser->loyaltyPoints);
        char choice;
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            *totalPrice = *totalPrice * 0.9;
            printf("10%% discount applied! New total: $%d\n", *totalPrice);
            loggedInUser->loyaltyPoints -= 50; // Deduct points
        }
    }
}

void paymentProcessing(int *totalPrice) {
    printf("Proceeding to payment...\n");
    printf("Total amount to be paid: $%d\n", *totalPrice);
    printf("Payment successful!\n");
    totalEarnings += *totalPrice; // Update total earnings
}

void updateUserProfile() {
    if (loggedInUser == NULL) {
        printf("\nPlease log in to update your profile.\n");
        return;
    }

    printf("Update Profile:\n");
    printf("1. Update Email\n");
    printf("2. Update Phone\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new email: ");
            scanf("%s", loggedInUser->email);
            printf("Email updated successfully!\n");
            break;
        case 2:
            printf("Enter new phone number: ");
            scanf("%s", loggedInUser->phone);
            printf("Phone number updated successfully!\n");
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}

void saveUserData() {
    FILE *file = fopen("users.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
}

void loadUserData() {
    FILE *file = fopen("users.dat", "rb");
    if (file == NULL) {
        // File doesn't exist, no users to load
        return;
    }
    fread(&userCount, sizeof(int), 1, file);
    fread(users, sizeof(User), userCount, file);
    fclose(file);
}

void sortMovies() {
    printf("Sort movies by:\n");
    printf("1. Rating\n");
    printf("2. Available Seats\n");
    printf("3. Price\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    for (int i = 0; i < MAX_MOVIES - 1; i++) {
        for (int j = i + 1; j < MAX_MOVIES; j++) {
            int swap = 0;
            if (movies[i].id != 0 && movies[j].id != 0) {
                switch (choice) {
                    case 1:
                        if (movies[i].rating < movies[j].rating) swap = 1;
                        break;
                    case 2:
                        if (movies[i].availableSeats < movies[j].availableSeats) swap = 1;
                        break;
                    case 3:
                        if (movies[i].pricePerSeat > movies[j].pricePerSeat) swap = 1;
                        break;
                    default:
                        printf("Invalid choice!\n");
                        return;
                }
                if (swap) {
                    Movie temp = movies[i];
                    movies[i] = movies[j];
                    movies[j] = temp;
                }
            }
        }
    }
    printf("Movies sorted successfully!\n");
}

void userRegistration() {
    if (userCount >= MAX_USERS) {
        printf("User registration limit reached.\n");
        return;
    }

    User newUser;
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);
    printf("Enter email: ");
    scanf("%s", newUser.email);
    printf("Enter phone number: ");
    scanf("%s", newUser.phone);

    newUser.bookingCount = 0;
    newUser.loyaltyPoints = 0;

    users[userCount++] = newUser;
    saveUserData();  // Save user data after registration
    printf("User registered successfully!\n");
}

void saveEarningsData() {
    FILE *file = fopen("earnings.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(&totalEarnings, sizeof(int), 1, file);
    fclose(file);
    printf("Earnings data saved successfully.\n");
}

void loadEarningsData() {
    FILE *file = fopen("earnings.dat", "rb");
    if (file == NULL) {
        // File doesn't exist, no earnings to load
        return;
    }
    fread(&totalEarnings, sizeof(int), 1, file);
    fclose(file);
    printf("Earnings data loaded successfully.\n");
}

void userLogin() {
    char username[50], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            loggedInUser = &users[i];
            saveUserData();  // Save user data after login
            printf("Login successful! Welcome, %s.\n", loggedInUser->username);
            return;
        }
    }

    printf("Invalid username or password!\n");
}

void logout() {
    if (loggedInUser == NULL) {
        printf("No user is logged in.\n");
        return;
    }

    printf("User %s logged out successfully!\n", loggedInUser->username);
    loggedInUser = NULL;
}

void mainMenu() {
    while (1) {
        printf("\nMain Menu:\n");
        printf("1. Display Movies\n");
        printf("2. Search Movie\n");
        printf("3. Book Ticket\n");
        printf("4. View Bookings\n");
        printf("5. Cancel Booking\n");
        printf("6. User Registration\n");
        printf("7. User Login\n");
        printf("8. Logout\n");
        printf("9. Update Profile\n");
        printf("10. Sort Movies\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayMovies(); break;
            case 2: searchMovie(); break;
            case 3: bookTicket(); break;
            case 4: viewBookings(); break;
            case 5: cancelBooking(); break;
            case 6: userRegistration(); break;
            case 7: userLogin(); break;
            case 8: logout(); break;
            case 9: updateUserProfile(); break;
            case 10: sortMovies(); break;
            case 11: return;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

void adminMenu() {
    while (1) {
        printf("\nAdmin Menu:\n");
        printf("1. Add Movie\n");
        printf("2. Remove Movie\n");
        printf("3. Generate Revenue Report\n");
        printf("4. Exit Admin Menu\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMovie(); break;
            case 2: removeMovie(); break;
            case 3: revenueReport(); break;
            case 4: return;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

void revenueReport() {
    printf("\n=========================================\n");
    printf("Total Revenue: $%d\n", totalEarnings);
    printf("=========================================\n");
}

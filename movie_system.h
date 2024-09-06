#ifndef MOVIE_SYSTEM_H
#define MOVIE_SYSTEM_H

// Function Prototypes
void initializeMovies();
void displayMovies();
void searchMovie();
void bookTicket();
void viewBookings();
void cancelBooking();
void addMovie();
void removeMovie();
void saveMovieData();
void loadMovieData();
void addReview(int movieId);
void displaySeatLayout(int movieId);
void seatSelection(int movieId, int *seatsBooked);
void applyDiscount(int *totalPrice);
void paymentProcessing(int *totalPrice);
void updateUserProfile();
void sortMovies();
void userRegistration();
void saveUserData();
void loadUserData();
void saveEarningsData();
void loadEarningsData();
void userLogin();
void logout();
void mainMenu();
void adminMenu();
void revenueReport();

#endif // MOVIE_SYSTEM_H

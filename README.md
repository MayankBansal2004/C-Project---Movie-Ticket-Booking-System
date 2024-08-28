# C-Project---Movie-Ticket-Booking-SystemHere's a README file.

---

# Movie Ticket Booking System

## Introduction

The Movie Ticket Booking System is a simple console-based C program that allows users to register, log in, search for movies, book tickets, and manage their bookings. The system also includes an admin menu for adding and removing movies, as well as generating revenue reports. The program is designed to be user-friendly, with various features for managing user bookings and applying loyalty points.

## Features

### User Features
- **User Registration & Login:** Users can register with a unique username and password. Registered users can log in to access additional features.
- **Search Movies:** Users can search for movies by name.
- **View Available Movies:** Displays a list of all available movies, including details like showtime, available seats, price per seat, and rating.
- **Book Tickets:** Logged-in users can book tickets for a selected movie, choose the number of seats, and apply loyalty points for discounts.
- **View Bookings:** Users can view their booking history, including details of each booking.
- **Cancel Bookings:** Users can cancel an existing booking, which refunds the seats back to the movie.
- **View Movie Details & Reviews:** Users can view detailed information about a movie, including user reviews. They can also add their own reviews.

### Admin Features
- **Add Movies:** Admins can add new movies to the system with details like name, showtime, available seats, price per seat, and rating.
- **Remove Movies:** Admins can remove movies from the system.
- **Revenue Report:** Admins can view the revenue generated by each movie, as well as the total revenue across all movies.

## Data Structures

- **Movie:** Stores information about each movie, including ID, name, showtime, available seats, price per seat, rating, and reviews.
- **Booking:** Stores information about each booking, including booking ID, customer name, movie ID, seats booked, and total price.
- **User:** Stores information about each user, including username, password, booking history, and loyalty points.

## Code Structure

The program consists of the following key functions:

### Initialization
- **`initializeMovies()`**: Initializes the movie database with a set of predefined movies.

### User Operations
- **`userRegistration()`**: Allows a new user to register.
- **`userLogin()`**: Allows a registered user to log in.
- **`logout()`**: Logs out the current user.

### Movie Operations
- **`displayMovies()`**: Displays a list of all available movies.
- **`searchMovie()`**: Allows users to search for a movie by name.
- **`viewMovieDetails()`**: Displays detailed information about a selected movie, including user reviews.
- **`addReview(int movieId)`**: Allows users to add a review to a movie.

### Booking Operations
- **`bookTicket()`**: Allows logged-in users to book tickets for a movie.
- **`viewBookings()`**: Displays the logged-in user's booking history.
- **`cancelBooking()`**: Allows users to cancel an existing booking.

### Admin Operations
- **`addMovie()`**: Allows the admin to add a new movie.
- **`removeMovie()`**: Allows the admin to remove a movie.
- **`revenueReport()`**: Generates a revenue report for the admin.

### Utility Functions
- **`applyDiscount(int *totalPrice)`**: Applies a discount to the total price based on the user's loyalty points.
- **`displaySeatLayout(int movieId)`**: Displays the seat layout for a selected movie (static layout in this version).

## How to Run

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/yourrepositoryname.git
   ```
2. **Navigate to the project directory:**
   ```bash
   cd yourrepositoryname
   ```
3. **Compile the program:**
   ```bash
   gcc movie_ticket_booking_system.c -o movie_ticket_booking_system
   ```
4. **Run the program:**
   ```bash
   ./movie_ticket_booking_system
   ```

## Future Enhancements

- **Dynamic Seat Selection:** Implementing a dynamic seat selection feature where users can select specific seats.
- **Advanced User Interface:** Enhancing the user interface with better input validation and more intuitive navigation.
- **Database Integration:** Replacing the static arrays with a database for more scalable and persistent data management.
- **Admin Authentication:** Adding a secure login system for admin access.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

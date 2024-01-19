#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_FLIGHTS 50
#define MAX_STRING_LENGTH 50
#define MIN_PASSWORD_LENGTH 8

typedef struct {
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
    float accountBalance;
} User;

typedef struct {
    char flightNumber[MAX_STRING_LENGTH];
    char destination[MAX_STRING_LENGTH];
    int availableSeats;
    float ticketPrice;
} Flight;

User users[MAX_USERS];
Flight flights[MAX_FLIGHTS];

int userCount = 0;
int flightCount = 0;

// Function prototypes
int authenticateUser();
int authenticateAdmin();
void registerUser();
void displayFlights();
void bookTicket(int userIndex);
void viewTicketDetails(int userIndex);

int main() {
    int choice;
    int loggedInUserIndex = -1; // Variable to store the index of the logged-in user

    // Admin credentials
    char adminUsername[] = "admin";
    char adminPassword[] = "adminpass";

    // Dummy flight data
    strcpy(flights[flightCount].flightNumber, "FL123");
    strcpy(flights[flightCount].destination, "New York");
    flights[flightCount].availableSeats = 50;
    flights[flightCount].ticketPrice = 500.0;
    flightCount++;

    while (1) {
        if (loggedInUserIndex == -1) {
            // User is not logged in
            printf("\n1. Register\n2. Login\n3. Exit\n");
        } else {
            // User is logged in
            printf("\n1. Display Flights\n2. Book Ticket\n3. View Ticket Details\n4. Logout\n");
        }

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                if (loggedInUserIndex == -1) {
                    registerUser();
                } else {
                    displayFlights();
                }
                break;
            case 2:
                if (loggedInUserIndex == -1) {
                    loggedInUserIndex = authenticateUser();
                } else {
                    bookTicket(loggedInUserIndex);
                }
                break;
            case 3:
                if (loggedInUserIndex == -1) {
                    exit(0);
                } else {
                    viewTicketDetails(loggedInUserIndex);
                    loggedInUserIndex = -1;
                }
                break;
            case 4:
                if (loggedInUserIndex != -1) {
                    loggedInUserIndex = -1;
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

int authenticateUser() {
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Enter your password: ");
            scanf("%s", password);
            if (strcmp(users[i].password, password) == 0) {
                printf("Login successful!\n");
                return i;
            } else {
                printf("Incorrect password. Login failed.\n");
                return -1;
            }
        }
    }

    printf("User not found. Login failed.\n");
    return -1;
}

int authenticateAdmin() {
    char adminUsername[MAX_STRING_LENGTH];
    char adminPassword[MAX_STRING_LENGTH];

    printf("Enter admin username: ");
    scanf("%s", adminUsername);

    printf("Enter admin password: ");
    scanf("%s", adminPassword);

    if (strcmp(adminUsername, "admin") == 0 && strcmp(adminPassword, "adminpass") == 0) {
        printf("Admin login successful!\n");
        return 1;
    } else {
        printf("Admin login failed.\n");
        return 0;
    }
}

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    printf("Enter your username: ");
    scanf("%s", users[userCount].username);

    char password[MAX_STRING_LENGTH];

    // Prompt user to set password
    do {
        printf("Enter your password: ");
        scanf("%s", password);

        if (strlen(password) < MIN_PASSWORD_LENGTH) {
            printf("Weak password. Password must be at least %d characters long.\n", MIN_PASSWORD_LENGTH);
        }
    } while (strlen(password) < MIN_PASSWORD_LENGTH);

    strcpy(users[userCount].password, password);
    users[userCount].accountBalance = 1000.0; // Initial account balance

    userCount++;
    printf("Registration successful!\n");
}

void displayFlights() {
    printf("\nAvailable Flights:\n");
    for (int i = 0; i < flightCount; i++) {
        printf("%d. %s to %s (%d seats available, $%.2f per ticket)\n", i + 1, flights[i].flightNumber, flights[i].destination, flights[i].availableSeats, flights[i].ticketPrice);
    }
}

void bookTicket(int userIndex) {
    displayFlights();

    int flightChoice;
    printf("Enter the number of the flight you want to book: ");
    scanf("%d", &flightChoice);

    if (flightChoice < 1 || flightChoice > flightCount) {
        printf("Invalid choice. Booking failed.\n");
        return;
    }

    int seatsToBook;
    printf("Enter the number of seats to book: ");
    scanf("%d", &seatsToBook);

    if (seatsToBook <= 0 || seatsToBook > flights[flightChoice - 1].availableSeats) {
        printf("Invalid number of seats. Booking failed.\n");
        return;
    }

    float totalCost = flights[flightChoice - 1].ticketPrice * seatsToBook;

    // Prompt user to confirm the booking
    printf("Confirm booking of %d seats for $%.2f? (1 for Yes, 0 for No): ", seatsToBook, totalCost);
    int confirmation;
    scanf("%d", &confirmation);

    if (confirmation != 1) {
        printf("Booking canceled.\n");
        return;
    }

    // Check if the user has sufficient funds
    if (totalCost > users[userIndex].accountBalance) {
        printf("Insufficient funds. Booking failed.\n");
        return;
    }

    // Update available seats and deduct the amount from the user's account
    flights[flightChoice - 1].availableSeats -= seatsToBook;
    users[userIndex].accountBalance -= totalCost;

    printf("Booking confirmed!\n");

    // Log the transaction in the user's history (in a real system, this information would be stored in a database)
    printf("Transaction Details:\n");
    printf("Flight Number: %s\n", flights[flightChoice - 1].flightNumber);
    printf("Destination: %s\n", flights[flightChoice - 1].destination);
    printf("Seats Booked: %d\n", seatsToBook);
    printf("Total Cost: $%.2f\n", totalCost);

    printf("Ticket booked successfully!\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ... (rest of the code)

void viewTicketDetails(int userIndex) {
    // In a real system, user-specific ticket details would be fetched from a database
    printf("Ticket Details:\n");
    printf("Passenger: %s\n", users[userIndex].username);
    printf("Flight Number: FL123\n");
    printf("Destination: New York\n");
    printf("Seats Booked: 2\n");
    printf("Total Cost: $1000.00\n");
    printf("Transaction Date: January 25, 2024\n");
}

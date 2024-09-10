#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DRIVERS 100
#define MAX_VEHICLES 100
#define MAX_USERS 100
#define MAX_ADMINS 10
#define MAX_BOOKINGS 100

// Structures
typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int hours;
    int minutes;
} Time;

typedef struct {
    int id;
    char name[50];
    int age;
    char licenseNumber[20];
    float pricePerKm;
    int available;
} Driver;

typedef struct {
    int id;
    char brand[20];
    char model[20];
    char plateNumber[20];
    float costPerKm;
    int status;
} Vehicle;

typedef struct {
    int id;
    int driverId;
    int vehicleId;
    float distance;
    float fare;
    Date date;
    Time time;
    char username[50];
    int completed;
} Booking;

typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    char username[50];
    char password[50];
} Admin;

// Global variables
Driver drivers[MAX_DRIVERS];
Vehicle vehicles[MAX_VEHICLES];
Booking bookings[MAX_BOOKINGS];
User users[MAX_USERS];
Admin admins[MAX_ADMINS];
int nextDriverId = 1;  // Start from 1 to reserve 0 as invalid ID
int nextVehicleId = 1; // Start from 1 to reserve 0 as invalid ID
int nextBookingId = 1; // Start from 1 to reserve 0 as invalid ID
int numUsers = 0;
int numAdmins = 0;

// Function prototypes
void initialize();
void menu();
void adminMenu();
void userMenu();
void addDriver(const char *name, int age, const char *licenseNumber, float pricePerKm);
void registerVehicle(const char *brand, const char *model, const char *plateNumber, float costPerKm);
void bookRide(const char *username);
float calculateFare(float distance);
void completeBooking();
void cancelBooking();
void displayPendingBookings();
void displayCompletedBookings();
void displayDrivers();
void displayVehicles();
void printMenuBorder();
void readUsersFromFile();
void writeUsersToFile();
void readAdminsFromFile();
void writeAdminsToFile();
void registerUser();
void registerAdmin();
void deleteDriver(int driverId);
void removeVehicle(int vehicleId);

int main() {
    initialize(); // Load initial data from files
    menu();       // Display menu
    writeUsersToFile(); // Save user data to file before exiting
    writeAdminsToFile(); // Save admin data to file before exiting
    return 0;
}

// Initialize function

void initialize() {
    readUsersFromFile();
    readAdminsFromFile();

    // Adding 10 drivers with specific details
    addDriver("John Doe", 35, "DL12345", 12.5);
    addDriver("Alice Smith", 28, "DL54321", 10.0);
    addDriver("Michael Johnson", 40, "DL98765", 15.0);
    addDriver("Emily Brown", 32, "DL67890", 11.5);
    addDriver("Robert Lee", 45, "DL24680", 13.0);
    addDriver("Jessica Wilson", 29, "DL13579", 9.5);
    addDriver("David Martinez", 38, "DL11223", 14.0);
    addDriver("Sarah Davis", 31, "DL998877", 12.0);
    addDriver("Christopher Garcia", 36, "DL665544", 11.0);
    addDriver("Jennifer Rodriguez", 33, "DL113355", 10.5);

    // Adding 10 vehicles with specific details
    registerVehicle("Toyota", "Camry", "ABC123", 8.0);
    registerVehicle("Honda", "Civic", "XYZ456", 7.5);
    registerVehicle("Ford", "Fusion", "DEF789", 9.0);
    registerVehicle("Chevrolet", "Malibu", "GHI012", 8.5);
    registerVehicle("Nissan", "Altima", "JKL345", 7.0);
    registerVehicle("Hyundai", "Elantra", "MNO678", 8.2);
    registerVehicle("Kia", "Optima", "PQR901", 7.8);
    registerVehicle("Volkswagen", "Passat", "STU234", 8.8);
    registerVehicle("Subaru", "Impreza", "VWX567", 7.3);
    registerVehicle("Mazda", "3", "YZA890", 7.7);
}




// Menu function
void menu() {
    int choice;
    do {
        printMenuBorder();
        printf("Main Menu\n");
        printMenuBorder();
        printf("1. Admin Registration \n");
        printf("2. Admin Login\n");
        printf("3. User Registration\n");
        printf("4. User Login\n");
        printf("5. Exit\n");
        printMenuBorder();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
         case 1:
                registerAdmin();
                break;
            case 2:
                adminMenu();
                break;
            case 3:
                registerUser();
                break;
            case 4:
                userMenu();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while (choice != 4);
}

// Admin menu function
void adminMenu() {
    char username[50], password[50];
    int loggedIn = 0;
    int choice;

    // Admin login
    printf("Admin Login\n");
    printf("Username: ");
    scanf(" %[^\n]s", username);
    printf("Password: ");
    scanf(" %[^\n]s", password);

    // Validate admin credentials
    for (int i = 0; i < numAdmins; i++) {
        if (strcmp(username, admins[i].username) == 0 && strcmp(password, admins[i].password) == 0) {
            loggedIn = 1;
            break;
        }
    }

    if (!loggedIn) {
        printf("Invalid credentials. Access denied.\n");
        return;
    }

    // Admin menu options
    do {
        printMenuBorder();
        printf("Admin Menu\n");
        printMenuBorder();
        printf("1. Add Driver\n");
        printf("2. Register Vehicle\n");
        printf("3. Delete Driver\n");
        printf("4. Remove Vehicle\n");
        printf("5. Display Drivers\n");
        printf("6. Display Vehicles\n");
        printf("7. Register Admin\n");
        printf("8. Back to Main Menu\n");
        printMenuBorder();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice) {
            case 1: {
                char name[50], licenseNumber[20];
                int age;
                float pricePerKm;
                printf("Enter driver name: ");
                scanf(" %[^\n]s", name);
                printf("Enter driver age: ");
                scanf("%d", &age);
                printf("Enter driver license number: ");
                scanf(" %[^\n]s", licenseNumber);
                printf("Enter price per km for the driver: ");
                scanf("%f", &pricePerKm);
                addDriver(name, age, licenseNumber, pricePerKm);
                writeAdminsToFile(); // Update admin data file after modification
                break;
            }
            case 2: {
                char brand[20], model[20], plateNumber[20];
                float costPerKm;
                printf("Enter vehicle brand: ");
                scanf(" %[^\n]s", brand);
                printf("Enter vehicle model: ");
                scanf(" %[^\n]s", model);
                printf("Enter vehicle plate number: ");
                scanf(" %[^\n]s", plateNumber);
                printf("Enter cost per km for the vehicle: ");
                scanf("%f", &costPerKm);
                registerVehicle(brand, model, plateNumber, costPerKm);
                writeAdminsToFile(); // Update admin data file after modification
                break;
            }
            case 3: {
                int driverId;
                printf("Enter driver ID to delete: ");
                scanf("%d", &driverId);
                deleteDriver(driverId);
                writeAdminsToFile(); // Update admin data file after modification
                break;
            }
            case 4: {
                int vehicleId;
                printf("Enter vehicle ID to remove: ");
                scanf("%d", &vehicleId);
                removeVehicle(vehicleId);
                writeAdminsToFile(); // Update admin data file after modification
                break;
            }
            case 5:
                displayDrivers();
                break;
            case 6:
                displayVehicles();
                break;
            case 7:
                registerAdmin();
                writeAdminsToFile(); // Update admin data file after modification
                break;
            case 8:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while(choice != 8);
}

// User menu function
void userMenu() {
    char username[50], password[50];
    int loggedIn = 0;
    int choice;

    // User login
    printf("User Login\n");
    printf("Username: ");
    scanf(" %[^\n]s", username);
    printf("Password: ");
    scanf(" %[^\n]s", password);

    // Validate user credentials
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            loggedIn = 1;
            break;
        }
    }

    if (!loggedIn) {
        printf("Invalid credentials. Access denied.\n");
        return;
    }

    // User menu options
    do {
        printMenuBorder();
        printf("User Menu\n");
        printMenuBorder();
        printf("1. Book Ride\n");
        printf("2. Complete Booking\n");
        printf("3. Cancel Booking\n");
        printf("4. Display Pending Bookings\n");
        printf("5. Display Completed Bookings\n");
        printf("6. Back to Main Menu\n");
        printMenuBorder();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice) {
            case 1:
                bookRide(username);
                break;
            case 2:
                completeBooking();
                break;
            case 3:
                cancelBooking();
                break;
            case 4:
                displayPendingBookings();
                break;
            case 5:
                displayCompletedBookings();
                break;
            case 6:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while(choice != 6);
}

// Function to add a driver
// Function to add a driver
void addDriver(const char *name, int age, const char *licenseNumber, float pricePerKm) {
    strcpy(drivers[nextDriverId].name, name);
    drivers[nextDriverId].age = age;
    strcpy(drivers[nextDriverId].licenseNumber, licenseNumber);
    drivers[nextDriverId].pricePerKm = pricePerKm;
    drivers[nextDriverId].available = 1;
    drivers[nextDriverId].id = nextDriverId;
    nextDriverId++;
    //printf("Driver added successfully with ID: %d\n", nextDriverId - 1);
}


// Function to register a vehicle

// Function to register a vehicle
void registerVehicle(const char *brand, const char *model, const char *plateNumber, float costPerKm) {
    strcpy(vehicles[nextVehicleId].brand, brand);
    strcpy(vehicles[nextVehicleId].model, model);
    strcpy(vehicles[nextVehicleId].plateNumber, plateNumber);
    vehicles[nextVehicleId].costPerKm = costPerKm;
    vehicles[nextVehicleId].status = 1;
    vehicles[nextVehicleId].id = nextVehicleId;
    nextVehicleId++;
    //printf("Vehicle registered successfully with ID: %d\n", nextVehicleId - 1);
}

// Function to delete a driver
void deleteDriver(int driverId) {
    if (driverId >= 1 && driverId < nextDriverId) {
        drivers[driverId].id = -1; // Mark as deleted
        printf("Driver with ID %d deleted successfully.\n", driverId);
    } else {
        printf("Driver ID %d not found.\n", driverId);
    }
}

// Function to remove a vehicle
void removeVehicle(int vehicleId) {
    if (vehicleId >= 1 && vehicleId < nextVehicleId) {
        vehicles[vehicleId].id = -1; // Mark as removed
        printf("Vehicle with ID %d removed successfully.\n", vehicleId);
    } else {
        printf("Vehicle ID %d not found.\n", vehicleId);
    }
}

// Function to register a new user
void registerUser() {
    if (numUsers < MAX_USERS) {
        printf("User Registration\n");
        printf("Enter username: ");
        scanf(" %[^\n]s", users[numUsers].username);
        printf("Enter password: ");

        scanf(" %[^\n]s", users[numUsers].password);

        numUsers++; // Increment the number of registered users
        printf("User registered successfully!\n");
    } else {
        printf("Maximum user registrations reached. Cannot register more users.\n");
    }
}

// Function to register a new admin

// Function to register a new admin
void registerAdmin() {
    if (numAdmins < MAX_ADMINS) {
        printf("Admin Registration\n");
        printf("Enter username: ");
        scanf(" %[^\n]s", admins[numAdmins].username);
        printf("Enter password: ");
        scanf(" %[^\n]s", admins[numAdmins].password);

        numAdmins++; // Increment the number of registered admins
        printf("Admin registered successfully!\n");

        // Optionally, you can write this admin's data to file immediately
        writeAdminsToFile();
    } else {
        printf("Maximum admin registrations reached. Cannot register more admins.\n");
    }
}

// Function to book a ride
void bookRide(const char *username) {
    int driverId, vehicleId;
    float distance;

    printf("Book Ride\n");
    printf("Enter driver ID: ");
    scanf("%d", &driverId);
    printf("Enter vehicle ID: ");
    scanf("%d", &vehicleId);
    printf("Enter distance (in km): ");
    scanf("%f", &distance);

    // Check if driver and vehicle are available
    if (driverId >= 1 && driverId < nextDriverId && drivers[driverId].available &&
        vehicleId >= 1 && vehicleId < nextVehicleId && vehicles[vehicleId].status) {

        // Calculate fare
        float fare = calculateFare(distance);

        // Create booking
        bookings[nextBookingId].id = nextBookingId;
        bookings[nextBookingId].driverId = driverId;
        bookings[nextBookingId].vehicleId = vehicleId;
        bookings[nextBookingId].distance = distance;
        bookings[nextBookingId].fare = fare;
        bookings[nextBookingId].date = (Date){0}; // Default to current date
        bookings[nextBookingId].time = (Time){0}; // Default to current time
        strcpy(bookings[nextBookingId].username, username);
        bookings[nextBookingId].completed = 0; // Booking is not completed yet
        nextBookingId++;

        // Mark driver and vehicle as unavailable
        drivers[driverId].available = 0;
        vehicles[vehicleId].status = 0;

        printf("Booking successful! Booking ID: %d\n", nextBookingId - 1);
    } else {
        printf("Invalid driver or vehicle ID, or driver/vehicle not available.\n");
    }
}

// Function to calculate fare based on distance
float calculateFare(float distance) {
    // Basic fare calculation logic (can be enhanced further)
    float baseFare = 50.0;
    float costPerKm = 10.0;
    return baseFare + distance * costPerKm;
}

// Function to complete a booking
void completeBooking() {
    int bookingId;
    printf("Complete Booking\n");
    printf("Enter booking ID to complete: ");
    scanf("%d", &bookingId);

    if (bookingId >= 1 && bookingId < nextBookingId && bookings[bookingId].completed == 0) {
        bookings[bookingId].completed = 1;
        printf("Booking ID %d completed successfully.\n", bookingId);
        // Mark driver and vehicle as available again
        int driverId = bookings[bookingId].driverId;
        int vehicleId = bookings[bookingId].vehicleId;
        if (driverId >= 1 && driverId < nextDriverId) {
            drivers[driverId].available = 1;
        }
        if (vehicleId >= 1 && vehicleId < nextVehicleId) {
            vehicles[vehicleId].status = 1;
        }
    } else {
        printf("Invalid booking ID or booking already completed.\n");
    }
}

// Function to cancel a booking
void cancelBooking() {
    int bookingId;
    printf("Cancel Booking\n");
    printf("Enter booking ID to cancel: ");
    scanf("%d", &bookingId);

    if (bookingId >= 1 && bookingId < nextBookingId && bookings[bookingId].completed == 0) {
        bookings[bookingId].completed = -1; // Mark as cancelled
        printf("Booking ID %d cancelled successfully.\n", bookingId);
        // Mark driver and vehicle as available again
        int driverId = bookings[bookingId].driverId;
        int vehicleId = bookings[bookingId].vehicleId;
        if (driverId >= 1 && driverId < nextDriverId) {
            drivers[driverId].available = 1;
        }
        if (vehicleId >= 1 && vehicleId < nextVehicleId) {
            vehicles[vehicleId].status = 1;
        }
    } else {
        printf("Invalid booking ID or booking already completed.\n");
    }
}

// Function to display pending bookings
void displayPendingBookings() {
    printf("Pending Bookings\n");
    printf("ID\tDriver\tVehicle\tDistance\tFare\tDate\tTime\tUsername\n");
    for (int i = 1; i < nextBookingId; i++) {
        if (bookings[i].completed == 0) {
            printf("%d\t%s\t%s\t%.2f\t%.2f\t%d/%d/%d\t%d:%d\t%s\n",
                   bookings[i].id,
                   drivers[bookings[i].driverId].name,
                   vehicles[bookings[i].vehicleId].brand,
                   bookings[i].distance,
                   bookings[i].fare,
                   bookings[i].date.day, bookings[i].date.month, bookings[i].date.year,
                   bookings[i].time.hours, bookings[i].time.minutes,
                   bookings[i].username);
        }
    }
}

// Function to display completed bookings
void displayCompletedBookings() {
    printf("Completed Bookings\n");
    printf("ID\tDriver\tVehicle\tDistance\tFare\tDate\tTime\tUsername\n");
    for (int i = 1; i < nextBookingId; i++) {
        if (bookings[i].completed != 0) {
            printf("%d\t%s\t%s\t%.2f\t%.2f\t%d/%d/%d\t%d:%d\t%s\n",
                   bookings[i].id,
                   drivers[bookings[i].driverId].name,
                   vehicles[bookings[i].vehicleId].brand,
                   bookings[i].distance,
                   bookings[i].fare,
                   bookings[i].date.day, bookings[i].date.month, bookings[i].date.year,
                   bookings[i].time.hours, bookings[i].time.minutes,
                   bookings[i].username);
        }
    }
}

// Function to display all registered drivers
void displayDrivers() {
    printf("Registered Drivers\n");
    printf("ID\tName\tAge\tLicense Number\tPrice per km\tAvailable\n");
    for (int i = 1; i < nextDriverId; i++) {
        if (drivers[i].id != -1) { // Check if driver is not deleted
            printf("%d\t%s\t%d\t%s\t%.2f\t%s\n",
                   drivers[i].id,
                   drivers[i].name,
                   drivers[i].age,
                   drivers[i].licenseNumber,
                   drivers[i].pricePerKm,
                   drivers[i].available ? "Yes" : "No");
        }
    }
}

// Function to display all registered vehicles
void displayVehicles() {
    printf("Registered Vehicles\n");
    printf("ID\tBrand\tModel\tPlate Number\tCost per km\tStatus\n");
    for (int i = 1; i < nextVehicleId; i++) {
        if (vehicles[i].id != -1) { // Check if vehicle is not removed
            printf("%d\t%s\t%s\t%s\t%.2f\t%s\n",
                   vehicles[i].id,
                   vehicles[i].brand,
                   vehicles[i].model,
                   vehicles[i].plateNumber,
                   vehicles[i].costPerKm,
                   vehicles[i].status ? "Available" : "Not Available");
        }
    }
}


// Function to print a border for the menu
void printMenuBorder() {
    printf("------------------------------------------\n");
}

// Function to read users' data from file
void readUsersFromFile() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Error opening users file for reading.\n");
        return;
    }

    while (fscanf(fp, "%s %s", users[numUsers].username, users[numUsers].password) != EOF) {
        numUsers++;
        if (numUsers >= MAX_USERS) {
            break;
        }
    }

    fclose(fp);
}

// Function to write users' data to file
void writeUsersToFile() {
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL) {
        printf("Error opening users file for writing.\n");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(fp, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(fp);
}

// Function to read admins' data from file
void readAdminsFromFile() {
    FILE *fp = fopen("admins.txt", "r");
    if (fp == NULL) {
        printf("Error opening admins file for reading.\n");
        return;
    }

    while (fscanf(fp, "%s %s", admins[numAdmins].username, admins[numAdmins].password) != EOF) {
        numAdmins++;
        if (numAdmins >= MAX_ADMINS) {
            break;
        }
    }

    fclose(fp);
}

// Function to write admins' data to file
void writeAdminsToFile() {
    FILE *fp = fopen("admins.txt", "w");
    if (fp == NULL) {
        printf("Error opening admins file for writing.\n");
        return;
    }

    for (int i = 0; i < numAdmins; i++) {
        fprintf(fp, "%s %s\n", admins[i].username, admins[i].password);
    }

    fclose(fp);
}

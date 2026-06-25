#include <iostream>
#include <string>
#include <fstream> // For file handling
#include <cstdlib> // For system()
using namespace std;
const int MAX_ROOMS = 25;
string adminPassword = "admin123";
// Room Arrays
int roomNumber[MAX_ROOMS] = {0};
string roomType[MAX_ROOMS];
double roomPrice[MAX_ROOMS]; // Price per day
bool roomAvailable[MAX_ROOMS] = {false};
// Customer Arrays
string customerName[MAX_ROOMS];
int customerRoomNumber[MAX_ROOMS] = {0};
string customerPhoneNumber[MAX_ROOMS];
string customerPackage[MAX_ROOMS];
int customerDays[MAX_ROOMS] = {0};
bool isCustomer[MAX_ROOMS] = {false};
// Function Prototypes
bool checkAdminLogin(const string&);   //checks password 
void addRoom();    //add new room and marks the room as available
void modifyRoom();  //update type and price
void removeRoom();   //deletes the room form system
void viewRooms();  //displays list of all rooms
void checkInCustomer();  
void checkOutCustomer();  //clears customer data and marks the room as available
void viewCustomerDetails();   
int findRoomIndex(int number);   //finds and returns array index of room
void saveCustomerToFile(int index, double totalBill);   //Saves customer booking and billing details to a file and Automatically opens the file using Notepad 
int main() {
    string enteredPassword;
    int choice;
    int attempts = 3;
    cout << "Welcome to Bella Villa Hotel\n";
    while (attempts--) {
        cout << "Enter Admin Password: ";
        cin >> enteredPassword;
        if (checkAdminLogin(enteredPassword)) break;
        else cout << "Incorrect password. Attempts left: " << attempts << endl;
        if (attempts == 0) {
            cout << "Too many failed attempts. Access denied.\n";
            return 0;
        }
    }
    do {
        cout << "\nAdmin Panel\n";
        cout << "1. Room Management\n";
        cout << "2. Customer Management\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int roomChoice;
                cout << "1. Add Room\n2. Modify Room\n3. Remove Room\n4. View Rooms\n";
                cout << "Enter your choice: ";
                cin >> roomChoice;
                switch (roomChoice) {
                    case 1: addRoom(); break;
                    case 2: modifyRoom(); break;
                    case 3: removeRoom(); break;
                    case 4: viewRooms(); break;
                    default: cout << "Invalid choice.\n"; break;
                }
                break;
            }
            case 2: {
                int customerChoice;
                cout << "1. Check-in\n2. Check-out\n3. View Customer Details\n";
                cout << "Enter your choice: ";
                cin >> customerChoice;
                switch (customerChoice) {
                    case 1: checkInCustomer(); break;
                    case 2: checkOutCustomer(); break;
                    case 3: viewCustomerDetails(); break;
                    default: cout << "Invalid choice.\n"; break;
                }
                break;
            }
            case 3: cout << "Logging out... Bye!" << endl; break;
            default: cout << "Invalid choice. Try again!" << endl;
        }
    } while (choice != 3);
    return 0;
}
bool checkAdminLogin(const string &password) {
    return password == adminPassword;
}
int findRoomIndex(int number) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (roomNumber[i] == number)
            return i;
    }
    return -1;
}
void addRoom() {
    int number;
    cout << "Enter Room Number: ";
    cin >> number;

    if (findRoomIndex(number) != -1) {
        cout << "This room number is already added.\n";
        return;
    }
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (roomNumber[i] == 0) {
            roomNumber[i] = number;
            int typeChoice;
            cout << "Select Room Type:\n1. Bronze\n2. Silver\n3. Gold\nEnter your choice: ";
            cin >> typeChoice;
            switch (typeChoice) {
                case 1: roomType[i] = "Bronze"; break;
                case 2: roomType[i] = "Silver"; break;
                case 3: roomType[i] = "Gold"; break;
                default: roomType[i] = "Bronze"; cout << "Invalid choice. Defaulting to Bronze.\n"; break;
            }
            cout << "Enter Room Price per Day: ";
            cin >> roomPrice[i];
            roomAvailable[i] = true;
            cout << "Room added successfully!\n";
            return;
        }
    }
    cout << "Room limit reached!\n";
}
void modifyRoom() {
    int number;
    cout << "Enter Room Number to modify: ";
    cin >> number;
    int index = findRoomIndex(number);
    if (index == -1) {
        cout << "Room not found!\n";
        return;
    }
    int typeChoice;
    cout << "Select new Room Type:\n1. Bronze\n2. Silver\n3. Gold\nEnter your choice: ";
    cin >> typeChoice;
    switch (typeChoice) {
        case 1: roomType[index] = "Bronze"; break;
        case 2: roomType[index] = "Silver"; break;
        case 3: roomType[index] = "Gold"; break;
        default: roomType[index] = "Bronze"; cout << "Invalid choice. Defaulting to Bronze.\n"; break;
    }
    cout << "Enter new Room Price per Day: ";
    cin >> roomPrice[index];
    cout << "Room details updated successfully!\n";
}
void removeRoom() {
    int number;
    cout << "Enter Room Number to remove: ";
    cin >> number;
    int index = findRoomIndex(number);
    if (index == -1) {
        cout << "Room not found!\n";
        return;
    }
    roomNumber[index] = 0;
    roomType[index] = "";
    roomPrice[index] = 0.0;
    roomAvailable[index] = false;
    isCustomer[index] = false;
    customerName[index] = "";
    customerPhoneNumber[index] = "";
    customerRoomNumber[index] = 0;
    customerPackage[index] = "";
    customerDays[index] = 0;
    cout << "Room removed successfully!\n";
}
void viewRooms() {
    cout << "\nList of All Rooms:\n";
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (roomNumber[i] != 0) {
            cout << "Room " << roomNumber[i]
                 << " | Type: " << roomType[i]
                 << " | Price/Day: " << roomPrice[i]
                 << " | Status: " << (roomAvailable[i] ? "Available" : "Booked") << "\n";
        }
    }
}
void checkInCustomer() {
    int packageChoice;
    string selectedPackage;
    double multiplier = 1.0;
    cout << "\nSelect Package:\n1. Bronze\n2. Silver\n3. Gold\nEnter your choice: ";
    cin >> packageChoice;
    switch (packageChoice) {
        case 1: selectedPackage = "Bronze"; multiplier = 1.0; break;
        case 2: selectedPackage = "Silver"; multiplier = 1.25; break;
        case 3: selectedPackage = "Gold"; multiplier = 1.5; break;
        default:
            cout << "Invalid choice. Defaulting to Bronze.\n";
            selectedPackage = "Bronze";
            multiplier = 1.0;
    }
    bool found = false;
    cout << "\nAvailable Rooms in " << selectedPackage << " category:\n";
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (roomAvailable[i] && roomType[i] == selectedPackage) {
            cout << "Room " << roomNumber[i] << " | Price/Day: " << roomPrice[i] << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No rooms available in this category.\n";
        return;
    }
    int selectedRoom;
    cout << "Enter Room Number to book: ";
    cin >> selectedRoom;
    int index = findRoomIndex(selectedRoom);
    if (index == -1 || !roomAvailable[index] || roomType[index] != selectedPackage) {
        cout << "Invalid room selection.\n";
        return;
    }
    cout << "Enter Customer Name: ";
    cin >> customerName[index];
    cout << "Enter Customer Phone Number: ";
    cin >> customerPhoneNumber[index];
    cout << "Enter number of days to stay: ";
    cin >> customerDays[index];
    double totalBill = roomPrice[index] * multiplier * customerDays[index];
    customerPackage[index] = selectedPackage;
    customerRoomNumber[index] = roomNumber[index];
    roomAvailable[index] = false;
    isCustomer[index] = true;
    cout << "\nCustomer checked in successfully!\n";
    cout << "Room Number: " << roomNumber[index] << "\n";
    cout << "Package: " << customerPackage[index] << "\n";
    cout << "Days: " << customerDays[index] << "\n";
    cout << "Price per Day: " << roomPrice[index] << "\n";
    cout << "Total Bill: " << totalBill << "\n";
    saveCustomerToFile(index, totalBill); // Save and open file 
}
void saveCustomerToFile(int index, double totalBill) {
    ofstream outFile("customers.txt");
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }
    outFile << "Customer Name: " << customerName[index] << "\n";
    outFile << "Phone Number: " << customerPhoneNumber[index] << "\n";
    outFile << "Room Number: " << customerRoomNumber[index] << "\n";
    outFile << "Package: " << customerPackage[index] << "\n";
    outFile << "Days: " << customerDays[index] << "\n";
    outFile << "Price/Day: " << roomPrice[index] << "\n";
    outFile << "Total Bill: " << totalBill << "\n";
    outFile << "---------------------------\n";
    outFile.close();
    // Automatically open the file in Notepad (Windows only)
    system("notepad customers.txt");
}
void checkOutCustomer() {
    int number;
    cout << "Enter Room Number for checkout: ";
    cin >> number;
    int index = findRoomIndex(number);
    if (index == -1 || !isCustomer[index]) {
        cout << "No customer found for this room.\n";
        return;
    }
    isCustomer[index] = false;
    customerRoomNumber[index] = 0;
    customerName[index] = "";
    customerPhoneNumber[index] = "";
    customerPackage[index] = "";
    customerDays[index] = 0;
    roomAvailable[index] = true;
    cout << "Customer checked out successfully!\n";
}
void viewCustomerDetails() {
    int number;
    cout << "Enter Room Number to view customer: ";
    cin >> number;
    int index = findRoomIndex(number);
    if (index != -1 && isCustomer[index]) {
        cout << "Customer Name: " << customerName[index]
             << ", Phone: " << customerPhoneNumber[index]
             << ", Room: " << customerRoomNumber[index]
             << ", Package: " << customerPackage[index]
             << ", Days: " << customerDays[index] << "\n";
    } else {
        cout << "No customer found in this room.\n";}}
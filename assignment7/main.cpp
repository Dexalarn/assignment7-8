#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // for std::system
#include "User.h"
#include "LibItem.h"
#include "LoadSave.h"

using namespace std;

// Function to clear the terminal screen
static void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

User* LogIn();
void MainPage();
void SecondPage();
void ManagerPage();

void SaveAll() {
    std::vector<User>& users = User::getUsers();
    std::vector<LibraryItem*>& LibItems = LibraryItem::getLibraryItems(); 
    // Save users and Library Items data before exiting
    SaveUsers(users, "users.json");
    SaveData(LibItems, "LibItems.json");
}

User* LogIn() {
    string name;
    string passwd;
    cout << "Name: ";
    cin >> name;
    cout << "Password: ";
    cin >> passwd;
    std::vector<User>& users = User::getUsers();
    for (auto& user : users) {
        if (name == user.getUsername() && passwd == user.getPassword()) {
            cout << "Welcome " << name << "!" << endl;
            return &user;
        }
    }
    cout << "Invalid credentials. Please try again." << endl;
    return nullptr;
}

void MainPage() {
    clearScreen();
    cout << " __   __  __   __    ___      ___   _______  ______    _______  ______    __   __  " << endl;
    cout << "|  |_|  ||  | |  |  |   |    |   | |  _    ||    _ |  |   _   ||    _ |  |  | |  | " << endl;
    cout << "|       ||  |_|  |  |   |    |   | | |_|   ||   | ||  |  |_|  ||   | ||  |  |_|  | " << endl;
    cout << "|       ||       |  |   |    |   | |       ||   |_||_ |       ||   |_||_ |       | " << endl;
    cout << "|       ||_     _|  |   |___ |   | |  _   | |    __  ||       ||    __  ||_     _| " << endl;
    cout << "| ||_|| |  |   |    |       ||   | | |_|   ||   |  | ||   _   ||   |  | |  |   |   " << endl;
    cout << "|_|   |_|  |___|    |_______||___| |_______||___|  |_||__| |__||___|  |_|  |___|  " << endl << endl;

    cout << "MAIN PAGE" << endl << endl;
    cout << "1. See available Library Items" << endl;
    cout << "2. Create account" << endl;
    cout << "3. Exit" << endl;
    cout << "4. Log In as Library Manager" << endl;

    int action;
    cin >> action;
    switch (action) {
    case 1:
        SecondPage();
        break;
    case 2:
        User::newUser();
        SaveAll();
        MainPage();
        break;
    case 3:
        break;
    case 4:
        ManagerPage();
        break;
    default:
        cout << "Error" << endl;
        MainPage();
        break;
    }
}

void SecondPage() {
    clearScreen();
    cout << "Log In" << endl;
    User* loggedUser = LogIn();
    if (loggedUser == nullptr) {
        return;
    }
    cout << "Library Items: " << endl << endl;
    LibraryItem::listLibraryItems(); // Corrected method name and class
    cout << "1. Borrow a Library Item " << endl;
    cout << "2. Return an Item" << endl;
    cout << "3. Exit " << endl;
    int action;
    cin >> action;
    switch (action) {
    case 1:
        if (loggedUser->LibItemLimit > loggedUser->inventory.size()) {
            cout << "Input Library Item ID you want to borrow: ";
            int LibItemID;
            cin >> LibItemID;
            bool LibItemFound = false;
            for (auto& LibItem : LibraryItem::getLibraryItems()) {
                if (LibItem->getId() == LibItemID) { // Changed to pointer access
                    LibItemFound = true;
                    LibItem->borrowLibItem(LibItem,loggedUser); 
                    
                }
            }
            if (!LibItemFound) {
                cout << "Library Item ID not found." << endl;
            }
            SaveAll();
            cin.ignore(); // Wait for user to press Enter
            cin.ignore();
            MainPage();
        }
        else {
            cout << "You reached the limit of amount of Library Items you can borrow" << endl;
            cout << "please return borrowed Library Items before taking a new one" << endl;
            cout << "1. return a Library Item" << endl;
            cout << "2. Exit" << endl;
            int action;
            cin >> action;
            if (action == 1) {
                clearScreen();
                LibraryItem::returnLibItem(loggedUser);
                SaveAll();
                MainPage();
            }
            else {
                MainPage();
            }
        }
        break;
    case 2:
        clearScreen();
        LibraryItem::returnLibItem(loggedUser);
        SaveAll();
        MainPage();
        break;
    case 3:
        MainPage();
        break;
    default:
        cout << "Error" << endl;
        MainPage();
        break;
    }
}

void ManagerPage() {
    clearScreen();
    cout << "Log In" << endl;
    User* loggedUser = LogIn();
    if (loggedUser == nullptr) {
        return;
    }
    if (loggedUser->Membership != 69420) {
        MainPage();
    }
    else {
        clearScreen();
        cout << "1. Add an Item" << endl;
        cout << "2. Main page" << endl;
        int HelpMeIAmTired;
        cin >> HelpMeIAmTired;
        switch (HelpMeIAmTired) {
        case 1:
            LibraryItem::AddItem();
            SaveAll();
            MainPage();
            break;
        case 2:
            MainPage();
            break;
        default:
            MainPage();
            break;
        }
        std::vector<LibraryItem*>& LibItems = LibraryItem::getLibraryItems(); // Changed to pointer type
        SaveData(LibItems, "LibItems.json");
    }
}

int main() {
    try {
        std::vector<User>& users = User::getUsers();
        std::vector<LibraryItem*>& LibItems = LibraryItem::getLibraryItems(); // Changed to pointer type
        LoadUsers(users, "users.json");
        LoadData(LibItems, "LibItems.json");

        MainPage();
        SaveAll();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred in main: " << e.what() << std::endl;
    }

    return 0;
}

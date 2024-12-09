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
void UserPage(User* loggedUser);
//void SecondPage();
//void ManagerPage();

void SaveAll() {
    std::vector<User*>& users = User::getUsers();
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
    std::vector<User*>& users = User::getUsers();
    for (auto& user : users) {
        if (name == user->getUsername() && passwd == user->getPassword()) {
            cout << "Welcome " << name << "!" << endl;
            return user;
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
    cout << "1. Log In" << endl;
    cout << "2. Create account" << endl;
    cout << "3. Exit" << endl;
    //cout << "4. Log In as Library Manager" << endl;

    int action;
    cin >> action;
    switch (action) {
    case 1:
        UserPage(LogIn());
        break;
    case 2:
        User::newUser();
        SaveAll();
        MainPage();
        break;
    case 3:

        break;
 
    default:
        cout << "Error" << endl;
        MainPage();
        break;
    }
}

static void UserPage(User* loggedUser) {
    while (true) {
        clearScreen();
        cout << "welcome back" << loggedUser->getInfo() << endl;
        cout << "Your items :" << endl;;
        if ((loggedUser->getInventory().size() == 0)) {
            cout << "Empty here :(" << endl;
        }
        else {
            loggedUser->listInventory();
        }

        cout << "1. Borrow item" << endl;
        cout << "2. Return item" << endl;
        cout << "3. exit" << endl;
        int action;
        cin >> action;
        int chosenItem;
        bool borrowed = false;
        bool returned = false;
        switch (action)
        {
        case 1:
            clearScreen();
            LibraryItem::listLibraryItems();
            cout << "ID of the item you want to borrow:" << endl;
            
            cin >> chosenItem;
            
            for (auto item : LibraryItem::getLibraryItems()) {
                if (item->getId() == chosenItem) {
                    loggedUser->borrowItem(*item);
                    cout << "item boorowed :)" << endl;
                    borrowed = true;
                    SaveAll();
                    cin.ignore();
                    break;
                }
            }
            if (borrowed) {break;}
            cout << "item not found" << endl;
            cin.ignore();
            cin.ignore();
            break;
        case 2:
            clearScreen();
            loggedUser->listInventory();
            cout << "ID of the item you want to return:" << endl;
            
            cin >> chosenItem;

            for (auto item : loggedUser->getInventory()) {
                if (item->getId() == chosenItem) {
                    loggedUser->returnItem(*item);
                    cout << "item returned :)" << endl;
                    returned = true;
                    SaveAll();
                    cin.ignore();
                    break;
                }
            }
            if (returned) { break; }
            cout << "item not found" << endl;
            cin.ignore();
            break;
        case 3:
            MainPage();
            break;
        default:
            break;
        }
        SaveAll();
    }
    
}




int main() {
    try {
        std::vector<User*>& users = User::getUsers();
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


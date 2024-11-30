#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // for std::system
#include "User.h"
#include "Book.h"
#include "LoadSave.h"

using namespace std;

// Function to clear the terminal screen
void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void MainPage();
void SecondPage();
void newUser();
User* LogIn();
void borrowBook();
void returnBook();

void newUser() {
    string name;
    string passwd;
    cout << "Write a name: ";
    cin >> name;
    cout << "Create a password: ";
    cin >> passwd;
    User::addUser(name, passwd);
    SaveUsers(User::getUsers(), "users.json"); // Save users after adding a new one
    cout << "Account created." << endl;
    cout << "Press Enter to clear the screen...";
    cin.ignore(); // Wait for user to press Enter
    cin.ignore();
    MainPage();
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
    // Main page
    cout << "MAIN PAGE" << endl << endl;
    cout << "1. See available books" << endl;
    cout << "2. Create account" << endl;
    cout << "3. Return Book" << endl;


    int action;
    cin >> action;
    switch (action) {
    case 1:
        SecondPage();
        break;
    case 2:
        newUser();
        break;
    case 3:
        returnBook();
        break;
    default:
        cout << "Error" << endl;
        break;
    }
}

void borrowBook() {
    cout << "Log In" << endl;
    User* loggedUser = LogIn();
    if (loggedUser == nullptr) {
        return;
    }

    cout << "Input book ID you want to borrow: ";
    int bookID;
    cin >> bookID;

    bool bookFound = false;
    for (auto& book : books) {
        if (book.ID == bookID) {
            bookFound = true;
            if (book.availability) {
                loggedUser->inventory.push_back(book);
                book.availability = false;
                cout << "Book borrowed successfully." << endl;
            }
            else {
                cout << "Book is not available." << endl;
            }
            break;
        }
    }

    if (!bookFound) {
        cout << "Book ID not found." << endl;
    }
    SaveUsers(User::getUsers(), "users.json");
    SaveData(books, "books.json");

    cin.ignore(); // Wait for user to press Enter
    cin.ignore();
    MainPage();

}

void returnBook() {
    clearScreen();
    cout << "Log In" << endl;
    User* loggedUser = LogIn();
    if (loggedUser == nullptr) {
        return;
    }
    User::listInventory(loggedUser);
    cout << "input ID of the book you want to return" << endl;
    int bookReturn;
    cin >> bookReturn;
    for (int i = 0; i < loggedUser->inventory.size(); i++) {
        if (loggedUser->inventory[i].ID == bookReturn) {
 
            loggedUser->inventory.erase(loggedUser->inventory.begin() + i);
            for (auto& book : books) {
                if (book.ID == bookReturn) {
                    book.availability = true;
                }
            }
            break;
        }
    }
    SaveUsers(User::getUsers(), "users.json");
    SaveData(books, "books.json");

    cin.ignore(); // Wait for user to press Enter
    cin.ignore();

    MainPage();

}

void SecondPage() {
    clearScreen();
    cout << "Books: " << endl << endl;
    Book::listBooks();
    cout << "1. Borrow a book " << endl;
    cout << "2. Exit " << endl;
    int action;
    cin >> action;
    switch (action) {
    case 1:
        borrowBook();
        break;
    case 2:
        MainPage();
        break;
    default:
        cout << "Error" << endl;
        break;
    }
}

int main() {
    try {
        std::vector<User>& users = User::getUsers();
        LoadUsers(users, "users.json");

        std::vector<Book>& books = Book::getBooks();
        LoadData(books, "books.json");

        MainPage();

        // Save users and books data before exiting
        SaveUsers(users, "users.json");
        SaveData(books, "books.json");
    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred in main: " << e.what() << std::endl;
    }

    return 0;
}

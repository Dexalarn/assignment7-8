#include "User.h"
#include "LibItem.h"
#include "LoadSave.h"
#include <iostream>
using namespace std;

static std::vector<User> users;

std::vector<User>& User::getUsers() {
    return users;
}

void User::listInventory() {
    for (int i = 0; i < this->inventory.size(); i++) {
        std::cout << this->inventory[i]->getId() << "   "
            << (dynamic_cast<Book*>(this->inventory[i]) ? "Book" : "Magazine") << "   "
            << "Due To Date: " << this->inventory[i]->getDueToDate()
            << std::endl;
    }
}

void User::newUser() {
    string name;
    string passwd;
    int mem;
    cout << "Write a name: ";
    cin >> name;
    cout << "Create a password: ";
    cin >> passwd;

    cout << "Member type: " << endl;
    cout << "1. GuestMemeber" << endl;
    cout << "2. StudentMemeber" << endl;
    cout << "3. FacultyMember" << endl;
    cin >> mem;
    if (mem == 1 || mem == 2 || mem == 3 || mem == 69420) {
        users.emplace_back(name, passwd, mem);
        SaveUsers(User::getUsers(), "users.json"); // Save users after adding a new one
        cout << "Account created." << endl;
        cout << "Press Enter to clear the screen...";
        cin.ignore(); // Wait for user to press Enter
        cin.ignore();
    }
    else {
        cout << "no such member type" << endl;
    }
}

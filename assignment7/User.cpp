#include "User.h"
#include "LibItem.h"
#include "LoadSave.h"
#include <iostream>
using namespace std;

vector<User*> users;

vector<User*>& User::getUsers() {
    return users;
}

void User::listInventory() {
    for (int i = 0; i < this->inventory.size(); i++) {
        cout << this->inventory[i]->getId() << "   "
            << (dynamic_cast<Book*>(this->inventory[i]) ? "Book" : "Magazine") << "   "
            << "Due To Date: " << this->inventory[i]->getDueToDate()
            << endl;
    }
}

void User::newUser() {
    string name;
    string passwd;
    int id;
    int mem;
    cout << "Write a name: ";
    cin >> name;
    cout << "Create a password: ";
    cin >> passwd;

    cout << "Member type: " << endl;
    cout << "1. GuestMember" << endl;
    cout << "2. StudentMember" << endl;
    cout << "3. FacultyMember" << endl;
    cin >> mem;
    if (mem == 1){
        id = std::stoi(to_string(users.size())) + 3001;  // it works but it is dumb (to be adjusted)
        GuestMember* user = new GuestMember(name, passwd, id);
        users.emplace_back(user);
        
    }
    else if (mem == 2) {
        id = std::stoi(to_string(users.size())) + 2001;
        StudentMember* user = new StudentMember(name, passwd, id);
        users.emplace_back(user);
        
    }
    else if (mem == 3) {
        id = std::stoi(to_string(users.size())) + 1001;
        FacultyMember* user = new FacultyMember(name, passwd, id);
        users.emplace_back(user);
    }
    else {
        cout << "no such member type" << endl;
    }
    
    SaveUsers(users, "users.json"); // Save users after adding a new one
    cout << "Account created." << endl;
    cout << "Press Enter to clear the screen...";
    cin.ignore(); // Wait for user to press Enter
    cin.ignore();
}

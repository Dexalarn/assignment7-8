#include "User.h"
#include <vector>
#include <iostream>

static std::vector<User> users;

std::vector<User>& User::getUsers() {
    return users;
}

void User::addUser(const std::string& username, const std::string& password) {
    users.emplace_back(username, password);
}
void User::listInventory(User* User) {
    for (int i = 0; i < User->inventory.size(); i++) {
        std::cout << User->inventory[i].ID 
            << User->inventory[i].name << "   "
            << User->inventory[i].date << "   "
            << User->inventory[i].writer << "   "
            << std::endl;
    }
}

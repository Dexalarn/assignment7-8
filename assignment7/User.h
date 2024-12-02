#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "LibItem.h"
class LibItem;
class User {
public:
    std::string username;
    std::string password;
    int Membership;
    int LibItemLimit = Membership*2-1;

    std::vector<LibItem> inventory;

    User(const std::string& username, const std::string& password, const int Membership)
        : username(username), password(password), Membership(Membership) {}

    static std::vector<User>& getUsers();
    static void newUser();
    void listInventory();


    const std::string& getUsername() const { return username; }
    const std::string& getPassword() const { return password; }
};

#endif // USER_H

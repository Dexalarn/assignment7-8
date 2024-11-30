#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Book.h"

class User {
public:
    std::string username;
    std::string password;
    std::vector<Book> inventory;

    User(const std::string& username, const std::string& password)
        : username(username), password(password) {}

    static std::vector<User>& getUsers();
    static void addUser(const std::string& username, const std::string& password);
    static void listInventory(User* loggedUser);


    const std::string& getUsername() const { return username; }
    const std::string& getPassword() const { return password; }
};

#endif // USER_H

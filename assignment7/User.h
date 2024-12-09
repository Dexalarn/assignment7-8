#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "LibItem.h"

class IMember {
public:
    virtual ~IMember() = default;
    virtual int getId() const = 0;
    virtual std::string getInfo() const = 0;
    virtual void borrowItem(LibraryItem& item) = 0;
    virtual void returnItem(LibraryItem& item) = 0;
};

class User : public IMember {
private:
    int id;
    std::string username;
    std::string password;
    std::vector<LibraryItem*> inventory;

public:
    // Constructor
    User(const std::string& username, const std::string& password, int id)
        : username(username), password(password), id(id) {}

    // Virtual destructor
    virtual ~User() = default;

    // Methods for encapsulation
    int getId() const override { return id; }
    std::string getInfo() const override {
        return "ID: " + std::to_string(id) + ", Name: " + username;
    }
    const std::string& getUsername() const { return username; }
    const std::string& getPassword() const { return password; }
    std::vector<LibraryItem*>& getInventory() { return inventory; }
    void listInventory();
    // Static functions 
    static std::vector<User*>& getUsers();
    static void newUser();
    

    void returnItem(LibraryItem& item) override {
        auto it = std::find(inventory.begin(), inventory.end(), &item);
        if (it != inventory.end()) {
            inventory.erase(it);
            item.returnItem();
        }
    }
};

class StudentMember : public User {
public:
    StudentMember(const std::string& name, const std::string& password, int id)
        : User(name, password, id) {}

    void borrowItem(LibraryItem& item) override {
        if (getInventory().size() < 3) {
            getInventory().push_back(&item);
            item.borrowItem();
        }
        else {
            throw std::runtime_error("Borrowing limit exceeded for Student Member");
        }
    }
};

class FacultyMember : public User {
public:
    FacultyMember(const std::string& name, const std::string& password, int id)
        : User(name, password, id) {}

    void borrowItem(LibraryItem& item) override {
        if (getInventory().size() < 5) {
            getInventory().push_back(&item);
            item.borrowItem();
        }
        else {
            throw std::runtime_error("Borrowing limit exceeded for Faculty Member");
        }
    }
};

class GuestMember : public User {
public:
    GuestMember(const std::string& name, const std::string& password, int id)
        : User(name, password, id) {}

    void borrowItem(LibraryItem& item) override {
        if (getInventory().size() < 1) {
            getInventory().push_back(&item);
            item.borrowItem();
        }
        else {
            throw std::runtime_error("Borrowing limit exceeded for Guest Member");
        }
    }
};

#endif // USER_H

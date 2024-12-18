#include "LoadSave.h"
#include "LibItem.h"
#include "User.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

void LoadData(std::vector<LibraryItem*>& LibItems, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Cannot open file for reading");
    }
    json jLibItems;
    inFile >> jLibItems;

    for (const auto& jLibItem : jLibItems) {
        int id = jLibItem.at("ID").get<int>();
        bool availability = jLibItem.at("availability").get<bool>();
        std::string type = jLibItem.at("type").get<std::string>();
        std::string dueToDate = jLibItem.at("dueToDate").get<std::string>();

        LibraryItem* item = nullptr;
        if (type == "Book") {
            std::string title = jLibItem.at("title").get<std::string>();
            item = new Book(id, availability, title);
        }
        else if (type == "Magazine") {
            std::string issue = jLibItem.at("issue").get<std::string>();
            item = new Magazine(id, availability, issue);
        }

        if (item) {
            item->setDueToDate(dueToDate);
            LibItems.push_back(item);
        }
    }
    inFile.close();
}

void SaveData(const std::vector<LibraryItem*>& LibItems, const std::string& filename) {
    json jLibItems = json::array();

    for (const auto& item : LibItems) {
        std::string type = dynamic_cast<Book*>(item) ? "Book" : "Magazine";

        if (type == "Book") {
            jLibItems.push_back({
                {"ID", item->getId()},
                {"title", item->getTitle()},
                {"availability", item->isAvailable()},
                {"dueToDate", item->getDueToDate()},
                {"type", type}
                });
        }
        else if (type == "Magazine") {
            jLibItems.push_back({
                {"ID", item->getId()},
                {"issue", item->getIssue()},
                {"availability", item->isAvailable()},
                {"dueToDate", item->getDueToDate()},
                {"type", type}
                });
        }
    }

    std::ofstream outFile(filename);
    outFile << jLibItems.dump(4); // Pretty-printing the JSON with an indent of 4 spaces
    outFile.close();

    std::cout << "Library Items data saved to " << filename << std::endl;
}

void LoadUsers(std::vector<User*>& users, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Cannot open file for reading");
    }
    json jUsers;
    inFile >> jUsers;

    for (const auto& jUser : jUsers) {
        if (jUser.contains("username") && jUser.contains("password") && jUser.contains("inventory") && jUser.contains("id")) {
            int id = jUser.at("id").get<int>();
            User* user = nullptr;

            if (id < 2000) {
                user = new FacultyMember(jUser.at("username").get<std::string>(), jUser.at("password").get<std::string>(), id);
            }
            else if (id >= 2000 && id < 3000) {
                user = new StudentMember(jUser.at("username").get<std::string>(), jUser.at("password").get<std::string>(), id);
            }
            else if (id >= 3000) {
                user = new GuestMember(jUser.at("username").get<std::string>(), jUser.at("password").get<std::string>(), id);
            }

            if (user) {
                for (const auto& jLibItem : jUser.at("inventory")) {
                    int itemId = jLibItem.at("ID").get<int>();
                    bool availability = jLibItem.at("availability").get<bool>();
                    std::string type = jLibItem.at("type").get<std::string>();
                    std::string dueToDate = jLibItem.at("dueToDate").get<std::string>();

                    LibraryItem* item = nullptr;
                    if (type == "Book") {
                        std::string title = jLibItem.at("title").get<std::string>();
                        item = new Book(itemId, availability, title);
                    }
                    else if (type == "Magazine") {
                        std::string issue = jLibItem.at("issue").get<std::string>();
                        item = new Magazine(itemId, availability, issue);
                    }

                    if (item) {
                        item->setDueToDate(dueToDate);
                        user->getInventory().push_back(item);
                    }
                }
                users.push_back(user);
            }
        }
        else {
            std::cerr << "Error: One of the user entries is missing required fields." << std::endl;
        }
    }
    inFile.close();
}

void SaveUsers(const std::vector<User*>& users, const std::string& filename) {
    json jUsers = json::array();
    
    for (const auto& user : users) {
        
        json jUser = {
            {"username", user->getUsername()},
            {"password", user->getPassword()},
            {"id", user->getId()}
        };
        json jInventory = json::array();
        for (auto& item : user->getInventory()) {
            if (dynamic_cast<Book*>(item)) {
                jInventory.push_back({
                    {"ID", item->getId()},
                    {"title", item->getTitle()},
                    {"availability", item->isAvailable()},
                    {"dueToDate", item->getDueToDate()},
                    {"type", "Book"}
                    });
            }
            else if (dynamic_cast<Magazine*>(item)) {
                jInventory.push_back({
                    {"ID", item->getId()},
                    {"issue", item->getIssue()},
                    {"availability", item->isAvailable()},
                    {"dueToDate", item->getDueToDate()},
                    {"type", "Magazine"}
                    });
            }
        }
        jUser["inventory"] = jInventory;
        jUsers.push_back(jUser);
    }

    std::ofstream outFile(filename);
    outFile << jUsers.dump(4); // Pretty-printing the JSON with an indent of 4 spaces
    outFile.close();

    std::cout << "Users data saved to " << filename << std::endl;
}

#include "LoadSave.h"
#include <fstream>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

void LoadData(std::vector<Book>& books, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Cannot open file for reading");
    }
    json jBooks;
    inFile >> jBooks;

    for (const auto& jBook : jBooks) {
        if (jBook.contains("name") && jBook.contains("date") && jBook.contains("writer") && jBook.contains("availability") && jBook.contains("ID")) {
            books.emplace_back(
                jBook.at("name").get<std::string>(),
                jBook.at("date").get<std::string>(),
                jBook.at("writer").get<std::string>(),
                jBook.at("availability").get<bool>(),
                jBook.at("ID").get<int>()
            );
        }
        else {
            std::cerr << "Error: One of the book entries is missing required fields." << std::endl;
        }
    }
    inFile.close();
}

void SaveData(const std::vector<Book>& books, const std::string& filename) {
    json jBooks = json::array();

    for (const auto& book : books) {
        jBooks.push_back({
            {"name", book.name},
            {"date", book.date},
            {"writer", book.writer},
            {"availability", book.availability},
            {"ID", book.ID}
            });
    }

    std::ofstream outFile(filename);
    outFile << jBooks.dump(4); // Pretty-printing the JSON with an indent of 4 spaces
    outFile.close();

    std::cout << "Books data saved to " << filename << std::endl;
}

void LoadUsers(std::vector<User>& users, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Cannot open file for reading");
    }
    json jUsers;
    inFile >> jUsers;

    for (const auto& jUser : jUsers) {
        if (jUser.contains("username") && jUser.contains("password") && jUser.contains("inventory")) {
            User user(
                jUser.at("username").get<std::string>(),
                jUser.at("password").get<std::string>()
            );
            for (const auto& jBook : jUser.at("inventory")) {
                user.inventory.emplace_back(
                    jBook.at("name").get<std::string>(),
                    jBook.at("date").get<std::string>(),
                    jBook.at("writer").get<std::string>(),
                    jBook.at("availability").get<bool>(),
                    jBook.at("ID").get<int>()
                );
            }
            users.push_back(user);
        }
        else {
            std::cerr << "Error: One of the user entries is missing required fields." << std::endl;
        }
    }
    inFile.close();
}

void SaveUsers(const std::vector<User>& users, const std::string& filename) {
    json jUsers = json::array();

    for (const auto& user : users) {
        json jUser = {
            {"username", user.getUsername()},
            {"password", user.getPassword()}
        };
        json jInventory = json::array();
        for (const auto& book : user.inventory) {
            jInventory.push_back({
                {"name", book.name},
                {"date", book.date},
                {"writer", book.writer},
                {"availability", book.availability},
                {"ID", book.ID}
                });
        }
        jUser["inventory"] = jInventory;
        jUsers.push_back(jUser);
    }

    std::ofstream outFile(filename);
    outFile << jUsers.dump(4); // Pretty-printing the JSON with an indent of 4 spaces
    outFile.close();

    std::cout << "Users data saved to " << filename << std::endl;
}

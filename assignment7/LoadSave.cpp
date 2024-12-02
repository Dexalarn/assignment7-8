#include "LoadSave.h"
#include <fstream>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

void LoadData(std::vector<LibItem>& LibItems, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Cannot open file for reading");
    }
    json jLibItems;
    inFile >> jLibItems;

    for (const auto& jLibItem : jLibItems) {
        if (jLibItem.contains("name") && jLibItem.contains("date") && jLibItem.contains("writer") && jLibItem.contains("availability") && jLibItem.contains("ID")) {
            LibItems.emplace_back(
                jLibItem.at("name").get<std::string>(),
                jLibItem.at("date").get<std::string>(),
                jLibItem.at("writer").get<std::string>(),
                jLibItem.at("availability").get<bool>(),
                jLibItem.at("ID").get<int>()
            );
        }
        else {
            std::cerr << "Error: One of the Library Item entries is missing required fields." << std::endl;
        }
    }
    inFile.close();
}

void SaveData(const std::vector<LibItem>& LibItems, const std::string& filename) {
    json jLibItems = json::array();

    for (const auto& LibItem : LibItems) {
        jLibItems.push_back({
            {"name", LibItem.name},
            {"date", LibItem.date},
            {"writer", LibItem.writer},
            {"availability", LibItem.availability},
            {"ID", LibItem.ID}
            });
    }

    std::ofstream outFile(filename);
    outFile << jLibItems.dump(4); // Pretty-printing the JSON with an indent of 4 spaces
    outFile.close();

    std::cout << "Library Items data saved to " << filename << std::endl;
}

void LoadUsers(std::vector<User>& users, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Cannot open file for reading");
    }
    json jUsers;
    inFile >> jUsers;

    for (const auto& jUser : jUsers) {
        if (jUser.contains("username") && jUser.contains("password") && jUser.contains("inventory") && jUser.contains("Membership")){
            User user(
                jUser.at("username").get<std::string>(),
                jUser.at("password").get<std::string>(),
                jUser.at("Membership").get<int>()
            );
            for (const auto& jLibItem : jUser.at("inventory")) {
                user.inventory.emplace_back(
                    jLibItem.at("name").get<std::string>(),
                    jLibItem.at("date").get<std::string>(),
                    jLibItem.at("writer").get<std::string>(),
                    jLibItem.at("availability").get<bool>(),
                    jLibItem.at("ID").get<int>()
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
            {"password", user.getPassword()},
            {"Membership", user.Membership}
        };
        json jInventory = json::array();
        for (const auto& LibItem : user.inventory) {
            jInventory.push_back({
                {"name", LibItem.name},
                {"date", LibItem.date},
                {"writer", LibItem.writer},
                {"availability", LibItem.availability},
                {"ID", LibItem.ID}
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

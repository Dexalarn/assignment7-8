#include "LibItem.h"
#include "User.h"
#include "LoadSave.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>


using namespace std;

std::vector<LibItem> LibItems;

std::vector<LibItem>& LibItem::getLibItems() {
    return LibItems;
}

void LibItem::listLibItems() {
    for (const auto& LibItem : LibItems) {
        std::cout << "ID: " << LibItem.ID << ", Name: " << LibItem.name
            << ", Date: " << LibItem.writer << ", Writer: " << LibItem.date << ", Availability: "
            << (LibItem.availability ? "Available" : "Not Available") << std::endl;
    }
}

void LibItem::borrowLibItem(User* loggedUser) {
    if (this->availability) {
        loggedUser->inventory.push_back(*this);
        this->availability = false;
        std::cout << "Item borrowed successfully." << std::endl;
    }
    else {
        std::cout << "Item is not available." << std::endl;
    }

    SaveUsers(User::getUsers(), "users.json");
    SaveData(LibItem::getLibItems(), "LibItems.json");
}

void LibItem::returnItem(User* loggedUser) {
    loggedUser->listInventory();
    std::cout << "input ID of the Library Item you want to return" << std::endl;
    int LibItemReturn;
    std::cin >> LibItemReturn;
    for (int i = 0; i < loggedUser->inventory.size(); i++) {
        if (loggedUser->inventory[i].ID == LibItemReturn) {
            loggedUser->inventory.erase(loggedUser->inventory.begin() + i);
            for (auto& LibItem : LibItems) {
                if (LibItem.ID == LibItemReturn) {
                    LibItem.availability = true;
                }
            }
            break;
        }
    }
    SaveUsers(User::getUsers(), "users.json");
    SaveData(LibItems, "LibItems.json");
}

void LibItem::AddItem() {
    std::string NewItemName;
    std::string NewItemDate;
    std::string NewItemWriter;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    std::cout << "Name:" << std::endl;
    std::cin >> NewItemName;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    std::cout << "Date:" << std::endl;
    std::cin >> NewItemDate;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    std::cout << "Writer:" << std::endl;
    std::cin >> NewItemWriter;

    LibItem::getLibItems().push_back(LibItem(NewItemName, NewItemDate, NewItemWriter, true, LibItem::getLibItems().size()+1));
}

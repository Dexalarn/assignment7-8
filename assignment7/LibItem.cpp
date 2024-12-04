#include "LibItem.h"
#include "User.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

std::vector<LibraryItem*> LibraryItems;

std::vector<LibraryItem*>& LibraryItem::getLibraryItems() {
    return LibraryItems;
}

void LibraryItem::listLibraryItems() {
    for (const auto& item : LibraryItems) {
        std::cout << "ID: " << item->getId()
            <<" " << item->returnType()
            << ",  " << (item->isAvailable() ? "Available" : ("Not Available until " + item->dueToDate))
            
            << std::endl;
    }
}

void LibraryItem::AddItem() {
    std::string itemType;
    std::cout << "Enter item type (Book/Magazine): ";
    std::cin >> itemType;

    int id = LibraryItem::getLibraryItems().size() + 1;
    bool availability = true;

    if (itemType == "Book") {
        std::string title;
        std::cout << "Enter title: "<<std::endl;
        std::cin.ignore();
        getline(std::cin, title);
        LibraryItem::getLibraryItems().push_back(new Book(id, availability,title));
    }
    else if (itemType == "Magazine") {
        std::string issue;
        std::cout << "Enter issue: " << std::endl;
        std::cin.ignore();
        getline(std::cin, issue);
        LibraryItem::getLibraryItems().push_back(new Magazine(id, availability,issue));
    }
    else {
        std::cout << "Invalid item type!" << std::endl;
    }
}

void LibraryItem::borrowLibItem(LibraryItem* item, User* user) {
    if (item->isAvailable()) {
        user->inventory.push_back(item);
        item->borrowItem();
        std::cout << "Item borrowed successfully." << std::endl;
    }
    else {
        std::cout << "Item is not available." << std::endl;
    }
}

void LibraryItem::returnLibItem(User* user) {
    user->listInventory();
    std::cout << "Input ID of the Library Item you want to return: ";
    int itemReturnId;
    std::cin >> itemReturnId;

    for (auto it = user->inventory.begin(); it != user->inventory.end(); ++it) {
        if ((*it)->getId() == itemReturnId) {
            (*it)->returnItem();
            user->inventory.erase(it);
            break;
        }
    }
}



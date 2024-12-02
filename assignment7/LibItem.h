#ifndef LibItem_H
#define LibItem_H

#include <string>
#include <vector>
#include "User.h"
class User;

class LibItem {
public:
    std::string name;
    std::string date;
    std::string writer;
    bool availability;
    int ID;

    LibItem(const std::string& name, const std::string& date,const std::string& writer, bool availability, int ID)
        : name(name), date(date),writer(writer), availability(availability), ID(ID) {}

    static std::vector<LibItem>& getLibItems();
    static void listLibItems();
    static void returnItem(User* loggedUser);
    void borrowLibItem(User* user);
    static void AddItem();

};



extern std::vector<LibItem> LibItems;

#endif // LibItem_H 

#ifndef LIBITEM_H
#define LIBITEM_H

#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>

class User; // Forward declaration

class LibraryItem {
private:
    int id;
    bool availability;
    std::string dueToDate;
public:
    //gett and set encapsulated parameters functions
    int getId() {
        return id;
    }
    bool isAvailable() {
        return availability;
    }
    void setAvailability(bool val) {
        availability = val;
    }
    std::string getDueToDate() {
        return dueToDate;
    }
    void setDueToDate(std::string val) {
        dueToDate = val;
    }
    //virtual functions to be overridden by subclasses
    virtual std::string getTitle() const {
        return "";
    }
    virtual std::string getIssue() const {
        return "";
    }
    //constructor
    LibraryItem(int id, bool availability)
        : id(id), availability(availability) {}
    //virtual destructor
    virtual ~LibraryItem() = default;

    virtual void borrowItem() = 0;

    
    virtual std::string returnType() = 0;

    //return item
    void returnItem() {
        setAvailability(true);
        setDueToDate(" ");
    }

    static std::vector<LibraryItem*>& getLibraryItems();
    static void borrowLibItem(LibraryItem* item, User* user);
    static void returnLibItem(User* user);
    static void listLibraryItems();
    static void AddItem();
};

class Book : public LibraryItem {
private:
    std::string type = "Book";
    std::string title;
public:
    //get encapsulated parameters
    std::string returnType() {
        return type;
    }
    std::string getTitle()const override {
        return title;
    }

    //constructor
    Book(int id, bool availability,std::string title)
        : LibraryItem(id, availability),title(title) {}

    void borrowItem() {
        setAvailability(false);
        struct tm newtime;
        time_t now = time(0);
        localtime_s(&newtime, &now);
        newtime.tm_mday += 28;
        mktime(&newtime);
        setDueToDate(std::to_string(newtime.tm_mday) + "." + std::to_string(newtime.tm_mon+1));

        
    }
};

class Magazine : public LibraryItem {
private:
    std::string type = "Magazine";
    std::string issue;
public:
    //get encapsulated parameters
    std::string returnType() {
        return type;
    }
    std::string getIssue()const override {
        return issue;
    }

    //constructor
    Magazine(int id, bool availability,std::string issue)
        : LibraryItem(id,availability), issue(issue) {}



    void borrowItem(){
        setAvailability(false);
        

        struct tm newtime;
        time_t now = time(0);
        localtime_s(&newtime, &now);
        newtime.tm_mday += 14;
        mktime(&newtime);
        setDueToDate( std::to_string(newtime.tm_mday) + "." + std::to_string(newtime.tm_mon+1));
    }
};

extern std::vector<LibraryItem*> LibraryItems;

#endif // LIBITEM_H

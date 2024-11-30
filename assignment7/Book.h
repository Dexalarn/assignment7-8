#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class Book {
public:
    std::string name;
    std::string date;
    std::string writer;
    bool availability;
    int ID;

    Book(const std::string& name, const std::string& date,const std::string& writer, bool availability, int ID)
        : name(name), date(date),writer(writer), availability(availability), ID(ID) {}

    static std::vector<Book>& getBooks();
    static void listBooks();
};

extern std::vector<Book> books;

#endif // BOOK_H

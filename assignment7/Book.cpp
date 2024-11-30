#include "Book.h"
#include <iostream>

std::vector<Book> books;

std::vector<Book>& Book::getBooks() {
    return books;
}

void Book::listBooks() {
    for (const auto& book : books) {
        std::cout << "ID: " << book.ID << ", Name: " << book.name
            << ", Date: " << book.writer << ", Writer: " << book.date << ", Availability: "
            << (book.availability ? "Available" : "Not Available") << std::endl;
    }
}

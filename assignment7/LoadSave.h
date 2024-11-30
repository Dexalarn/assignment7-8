#ifndef LOADSAVE_H
#define LOADSAVE_H

#include <vector>
#include <string>
#include "User.h"
#include "Book.h"

void LoadData(std::vector<Book>& books, const std::string& filename);
void SaveData(const std::vector<Book>& books, const std::string& filename);

void LoadUsers(std::vector<User>& users, const std::string& filename);
void SaveUsers(const std::vector<User>& users, const std::string& filename);

#endif // LOADSAVE_H

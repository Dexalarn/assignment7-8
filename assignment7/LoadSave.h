// LoadSave.h
#ifndef LOADSAVE_H
#define LOADSAVE_H

#include <vector>
#include <string>
#include "User.h"
#include "LibItem.h"

void LoadData(std::vector<LibraryItem*>& LibItems, const std::string& filename);
void SaveData(const std::vector<LibraryItem*>& LibItems, const std::string& filename);
void LoadUsers(std::vector<User*>& users, const std::string& filename);  // Ensure this is non-const reference
void SaveUsers(const std::vector<User*>& users, const std::string& filename);  // Ensure this is non-const reference

#endif // LOADSAVE_H

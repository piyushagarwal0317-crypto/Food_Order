#pragma once
#include <vector>
#include <string>
#include "MenuItem.h"

class Menu {
private:
    std::vector<MenuItem> items;

public:
    void loadMenuFromFile(const std::string& filename);
    void addItem(const MenuItem& item);
    void displayMenu() const;
    MenuItem getItemById(int id) const;
    std::vector<MenuItem> getItems() const;
};
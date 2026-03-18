#include "Menu.h"
#include <iostream>
#include <stdexcept>
#include <fstream>   // For reading files
#include <sstream>   // For splitting strings

void Menu::loadMenuFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, priceStr, category;

        // Read up to each comma
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, priceStr, ',');
        std::getline(ss, category, ','); // Grab the new category!

        // If the line wasn't empty, create the item and add it to the list
        if (!idStr.empty()) {
            int id = std::stoi(idStr);
            double price = std::stod(priceStr);
            items.push_back(MenuItem(id, name, price, category));
        }
    }
}

void Menu::addItem(const MenuItem& item) {
    items.push_back(item);
}

void Menu::displayMenu() const {
    std::cout << "\n--- Restaurant Menu ---\n";
    for (const auto& item : items) {
        std::cout << "[" << item.getId() << "] " 
                  << item.getName() << " - $" 
                  << item.getPrice() << " (" 
                  << item.getCategory() << ")\n";
    }
    std::cout << "-----------------------\n";
}

MenuItem Menu::getItemById(int id) const {
    for (const auto& item : items) {
        if (item.getId() == id) {
            return item;
        }
    }
    // If the user types a wrong ID, we throw an error
    throw std::runtime_error("Item ID not found!");
}
std::vector<MenuItem> Menu::getItems() const {
    return items;
}
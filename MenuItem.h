#pragma once
#include <string>

class MenuItem {
private:
    int id;
    std::string name;
    double price;
    std::string category;

public:
    MenuItem(int id, std::string name, double price, std::string category)
        : id(id), name(name), price(price), category(category) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    std::string getCategory() const { return category; }
};
#include "Menu.h"
#include <iostream>
#include <stdexcept>
#include <fstream>   // For reading files
#include <sstream>   // For splitting strings
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

void Menu::loadMenuFromFile(const std::string& filename) {
    // 1. Convert the standard C++ string to a Qt String
    QString qtFilename = QString::fromStdString(filename);

    // 2. Open the file using Qt's QFile (This understands the ":/" secret path!)
    QFile file(qtFilename);

    // 3. Check if the file successfully opened
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "CRITICAL ERROR: Could not open menu file at:" << qtFilename;
        return;
    }

    // 4. Read the file line by line
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        // Skip empty lines just in case there are blank spaces at the bottom of the text file
        if (line.trimmed().isEmpty()) {
            continue;
        }

        // 5. Split the line into a list using the comma as the separator
        QStringList parts = line.split(',');

        // 6. Make sure the line actually has all 4 pieces of data!
        if (parts.size() >= 4) {
            // Grab the data, trim off extra spaces, and convert back to C++ formats
            int id = parts[0].trimmed().toInt();
            std::string name = parts[1].trimmed().toStdString();
            double price = parts[2].trimmed().toDouble();
            std::string category = parts[3].trimmed().toStdString();

            // Push it into your C++ list!
            items.push_back(MenuItem(id, name, price, category));
        }
    }

    // 7. Always close the file
    file.close();
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
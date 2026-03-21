#include "Order.h"
#include <iostream>
#include <fstream>
#include <iomanip>  // For std::setw, std::fixed, std::setprecision
#include <ctime>    // For getting the live time

void Order::addItemToCart(const MenuItem& item, int quantity) {
    cart.push_back({item, quantity});
    std::cout << quantity << "x " << item.getName() << " added to cart.\n";
}

void Order::displayCart() const {
    std::cout << "\n--- Your Cart ---\n";
    if (cart.empty()) {
        std::cout << "Cart is empty.\n";
        return;
    }

    for (const auto& orderItem : cart) {
        std::cout << orderItem.item.getName() << " x" << orderItem.quantity
                  << " : $" << (orderItem.item.getPrice() * orderItem.quantity) << "\n";
    }
}

double Order::calculateTotal() const {
    double total = 0.0;
    for (const auto& orderItem : cart) {
        total += (orderItem.item.getPrice() * orderItem.quantity);
    }
    return total;
}

void Order::clearCart() {
    cart.clear();
    std::cout << "Cart has been cleared.\n";
}

void Order::saveReceiptToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error: Could not save receipt.\n";
        return;
    }

    // 1. Get the current date and time
    std::time_t t = std::time(nullptr);
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&t));

    // 2. Print the Professional Header
    file << "========================================\n";
    file << "               FOOD VILLA               \n";
    file << "         123 Culinary Boulevard         \n";
    file << "           Tel: (555) 123-4567          \n";
    file << "========================================\n";
    file << " Date: " << timeStr << "\n";
    file << "========================================\n";

    // 3. Print the Column Headers
    file << std::left << std::setw(6) << "Qty"
         << std::setw(24) << "Item"
         << std::right << std::setw(10) << "Price" << "\n";
    file << "----------------------------------------\n";

    // 4. Print the Cart Items using your exact variables!
    for (const auto& orderItem : cart) {
        // Calculate the total price for this specific row (Price * Qty)
        double lineTotal = orderItem.item.getPrice() * orderItem.quantity;

        file << std::left << std::setw(6) << orderItem.quantity
             << std::setw(24) << orderItem.item.getName()
             << "$" << std::right << std::setw(9) << std::fixed << std::setprecision(2) << lineTotal << "\n";
    }

    // 5. Print the Footer and Total
    file << "----------------------------------------\n";
    file << std::right << std::setw(30) << "Total: "
         << "$" << std::fixed << std::setprecision(2) << calculateTotal() << "\n";
    file << "========================================\n";
    file << "       Thank you for your visit!        \n";
    file << "         Please come again.             \n";
    file << "========================================\n";

    file.close();
    std::cout << "Receipt saved to " << filename << "\n";
}

void Order::removeOrderItem(int index) {
    // Failsafe: Make sure the index actually exists in the cart before trying to delete it!
    if (index >= 0 && index < static_cast<int>(cart.size())) {
        // .erase() is the standard C++ way to remove an item from a vector
        cart.erase(cart.begin() + index);
    }
}
#include "Order.h"
#include <iostream>
#include <fstream>

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

    file << "--- RESTAURANT RECEIPT ---\n";
    for (const auto& orderItem : cart) {
        file << orderItem.item.getName() << " x" << orderItem.quantity
             << " : $" << (orderItem.item.getPrice() * orderItem.quantity) << "\n";
    }
    file << "--------------------------\n";
    file << "TOTAL: $" << calculateTotal() << "\n";

    file.close();
    std::cout << "Receipt saved to " << filename << "\n";
}
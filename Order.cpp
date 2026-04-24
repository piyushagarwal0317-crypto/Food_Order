#include "Order.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

// Returns the index in cart (existing or newly added)
int Order::addItemToCart(const MenuItem& item, int quantity) {
    // Search for an existing entry with the same item ID
    for (int i = 0; i < (int)cart.size(); i++) {
        if (cart[i].item.getId() == item.getId()) {
            cart[i].quantity += quantity; // already in cart — just bump the count
            return i;
        }
    }
    // Not found — add a brand new entry
    cart.push_back({item, quantity});
    return (int)cart.size() - 1;
}

// Returns true if the item was fully removed, false if just decremented
bool Order::removeOrderItem(int index) {
    if (index < 0 || index >= (int)cart.size()) return false;

    if (cart[index].quantity > 1) {
        cart[index].quantity--;  // still has stock, just reduce
        return false;
    } else {
        cart.erase(cart.begin() + index); // last one — remove the row entirely
        return true;
    }
}

int Order::getQuantity(int index) const {
    if (index < 0 || index >= (int)cart.size()) return 0;
    return cart[index].quantity;
}

void Order::displayCart() const {
    std::cout << "\n--- Your Cart ---\n";
    if (cart.empty()) { std::cout << "Cart is empty.\n"; return; }
    for (const auto& o : cart) {
        std::cout << o.item.getName() << " x" << o.quantity
                  << " : $" << (o.item.getPrice() * o.quantity) << "\n";
    }
}

double Order::calculateTotal() const {
    double total = 0.0;
    for (const auto& o : cart) total += o.item.getPrice() * o.quantity;
    return total;
}

void Order::clearCart() {
    cart.clear();
}

void Order::saveReceiptToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) { std::cout << "Error: Could not save receipt.\n"; return; }

    std::time_t t = std::time(nullptr);
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&t));

    file << "========================================\n";
    file << "               FOOD VILLA               \n";
    file << "         123 Culinary Boulevard         \n";
    file << "           Tel: (555) 123-4567          \n";
    file << "========================================\n";
    file << " Date: " << timeStr << "\n";
    file << "========================================\n";
    file << std::left  << std::setw(6)  << "Qty"
         << std::setw(24) << "Item"
         << std::right << std::setw(10) << "Price" << "\n";
    file << "----------------------------------------\n";

    for (const auto& o : cart) {
        double lineTotal = o.item.getPrice() * o.quantity;
        file << std::left  << std::setw(6)  << o.quantity        // e.g. "3"
             << std::setw(24) << o.item.getName()                // e.g. "Cheeseburger"
             << "$" << std::right << std::setw(9)
             << std::fixed << std::setprecision(2) << lineTotal << "\n";
    }

    file << "----------------------------------------\n";
    file << std::right << std::setw(30) << "Total: "
         << "$" << std::fixed << std::setprecision(2) << calculateTotal() << "\n";
    file << "========================================\n";
    file << "       Thank you for your visit!        \n";
    file << "         Please come again.             \n";
    file << "========================================\n";
    file.close();
}
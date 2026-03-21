#pragma once
#include <vector>
#include "MenuItem.h"

class Order {
private:
    // Helper structure to bundle an item with its quantity
    struct OrderItem {
        MenuItem item;
        int quantity;
    };
    
    std::vector<OrderItem> cart;

public:
    void addItemToCart(const MenuItem& item, int quantity);
    void saveReceiptToFile(const std::string& filename) const;
    void displayCart() const;
    double calculateTotal() const;
    void clearCart();
    void removeOrderItem(int index);
};
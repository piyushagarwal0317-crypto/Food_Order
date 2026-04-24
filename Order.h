#pragma once
#include <vector>
#include "MenuItem.h"

class Order {
private:
    struct OrderItem {
        MenuItem item;
        int quantity;
    };
    std::vector<OrderItem> cart;

public:
    int  addItemToCart(const MenuItem& item, int quantity); // now returns cart index
    int  getQuantity(int index) const;                      // new: lets UI read qty
    bool removeOrderItem(int index);                        // now returns true if fully removed
    void saveReceiptToFile(const std::string& filename) const;
    void displayCart() const;
    double calculateTotal() const;
    void clearCart();
};
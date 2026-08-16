#ifndef BILLING_H
#define BILLING_H

#include <vector>
#include <string>
#include "Inventory.h"

struct BillItem {
    int productId;
    std::string productName;
    int quantity;
    double unitPrice;

    double total() const {
        return quantity * unitPrice;
    }
};

class Billing {
private:
    std::vector<BillItem> items;

public:
    bool addItem(Inventory& inventory, int productId, int quantity);
    double subtotal() const;
    double calculateGST(double rate = 18.0) const;
    double grandTotal(double gstRate = 18.0) const;
    bool isEmpty() const;

    void clear();
    void printBill(double gstRate = 18.0) const;
    bool saveBill(double gstRate = 18.0,
                  const std::string& directory = "data") const;
};
#endif

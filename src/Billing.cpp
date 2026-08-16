#include "Billing.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <sstream>

bool Billing::addItem(Inventory& inventory, int productId, int quantity) {
    if (quantity <= 0) return false;

    Product* product = inventory.findProduct(productId);
    if (!product || product->getQuantity() < quantity) return false;

    // If the same product is added again, combine quantities.
    for (auto& item : items) {
        if (item.productId == productId) {
            if (product->getQuantity() < item.quantity + quantity) return false;
            product->setQuantity(product->getQuantity() - quantity);
            item.quantity += quantity;
            return inventory.save();
        }
    }

    BillItem item{
        product->getId(),
        product->getName(),
        quantity,
        product->getPrice()
    };

    product->setQuantity(product->getQuantity() - quantity);
    items.push_back(item);

    return inventory.save();
}

double Billing::subtotal() const {
    double total = 0.0;
    for (const auto& item : items) total += item.total();
    return total;
}

double Billing::calculateGST(double rate) const {
    return subtotal() * rate / 100.0;
}

double Billing::grandTotal(double gstRate) const {
    return subtotal() + calculateGST(gstRate);
}

bool Billing::isEmpty() const {
    return items.empty();
}

void Billing::clear() {
    items.clear();
}

void Billing::printBill(double gstRate) const {
    if (items.empty()) {
        std::cout << "\nNo items in bill.\n";
        return;
    }

    std::cout << "\n========== CUSTOMER BILL ==========\n";
    std::cout << std::left << std::setw(8) << "ID"
              << std::setw(22) << "Product"
              << std::setw(8) << "Qty"
              << std::setw(12) << "Price"
              << std::setw(12) << "Total" << "\n";

    std::cout << "--------------------------------------------------------------\n";

    std::cout << std::fixed << std::setprecision(2);

    for (const auto& item : items) {
        std::cout << std::left << std::setw(8) << item.productId
                  << std::setw(22) << item.productName.substr(0, 20)
                  << std::setw(8) << item.quantity
                  << std::setw(12) << item.unitPrice
                  << std::setw(12) << item.total() << "\n";
    }

    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Subtotal : Rs. " << subtotal() << "\n";
    std::cout << "GST      : Rs. " << calculateGST(gstRate) << "\n";
    std::cout << "TOTAL    : Rs. " << grandTotal(gstRate) << "\n";
    std::cout << "==============================================================\n";
}

bool Billing::saveBill(double gstRate, const std::string& directory) const {
    if (items.empty()) return false;

    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);

    std::ostringstream filename;
    filename << directory << "/bill_"
             << (local->tm_year + 1900)
             << (local->tm_mon + 1)
             << local->tm_mday << "_"
             << local->tm_hour
             << local->tm_min
             << local->tm_sec << ".txt";

    std::ofstream file(filename.str());
    if (!file) return false;

    file << "========== CUSTOMER BILL ==========\n";
    file << std::fixed << std::setprecision(2);

    for (const auto& item : items) {
        file << item.productName << " | Qty: "
             << item.quantity << " | Unit Price: Rs. "
             << item.unitPrice << " | Total: Rs. "
             << item.total() << "\n";
    }

    file << "-----------------------------------\n";
    file << "Subtotal: Rs. " << subtotal() << "\n";
    file << "GST: Rs. " << calculateGST(gstRate) << "\n";
    file << "Grand Total: Rs. " << grandTotal(gstRate) << "\n";

    return true;
}

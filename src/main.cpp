#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Inventory.h"
#include "Billing.h"
#include "Utils.h"

using namespace std;

void showProduct(const Product& p) {
    cout << left
         << setw(8) << p.getId()
         << setw(24) << p.getName().substr(0, 22)
         << setw(12) << fixed << setprecision(2) << p.getPrice()
         << setw(10) << p.getQuantity()
         << setw(12) << p.getReorderLevel();

    if (p.isLowStock()) cout << "LOW";
    cout << "\n";
}

void displayProducts(const Inventory& inventory) {
    const auto& products = inventory.getProducts();

    if (products.empty()) {
        cout << "\nNo products available.\n";
        return;
    }

    cout << "\n================ PRODUCT LIST ================\n";
    cout << left
         << setw(8) << "ID"
         << setw(24) << "Name"
         << setw(12) << "Price"
         << setw(10) << "Stock"
         << setw(12) << "Reorder"
         << "Status\n";

    cout << "---------------------------------------------------------------\n";

    for (const auto& product : products) {
        showProduct(product);
    }
}

void addProduct(Inventory& inventory) {
    cout << "\n========== ADD PRODUCT ==========\n";

    int id = Utils::readInt("Product ID: ", 1, 999999);
    string name = Utils::readNonEmptyString("Product name: ");
    double price = Utils::readDouble("Price: Rs. ", 0.0);
    int quantity = Utils::readInt("Initial quantity: ", 0, 1000000);
    int reorder = Utils::readInt("Low-stock level: ", 0, 1000000);

    Product product(id, name, price, quantity, reorder);

    if (inventory.addProduct(product)) {
        cout << "Product added successfully.\n";
    } else {
        cout << "Could not add product. ID may already exist.\n";
    }
}

void updateProduct(Inventory& inventory) {
    int id = Utils::readInt("Enter product ID to update: ", 1, 999999);

    Product* product = inventory.findProduct(id);

    if (!product) {
        cout << "Product not found.\n";
        return;
    }

    string name = Utils::readNonEmptyString("New name: ");
    double price = Utils::readDouble("New price: Rs. ", 0.0);
    int quantity = Utils::readInt("New quantity: ", 0, 1000000);
    int reorder = Utils::readInt("New low-stock level: ", 0, 1000000);

    if (inventory.updateProduct(id, name, price, quantity, reorder)) {
        cout << "Product updated successfully.\n";
    } else {
        cout << "Update failed.\n";
    }
}

void deleteProduct(Inventory& inventory) {
    int id = Utils::readInt("Enter product ID to delete: ", 1, 999999);

    if (inventory.deleteProduct(id)) {
        cout << "Product deleted successfully.\n";
    } else {
        cout << "Product not found or deletion failed.\n";
    }
}

void searchProduct(const Inventory& inventory) {
    int id = Utils::readInt("Enter product ID: ", 1, 999999);
    const Product* product = inventory.findProduct(id);

    if (!product) {
        cout << "Product not found.\n";
        return;
    }

    cout << "\nProduct found:\n";
    cout << "ID: " << product->getId() << "\n";
    cout << "Name: " << product->getName() << "\n";
    cout << "Price: Rs. " << fixed << setprecision(2) << product->getPrice() << "\n";
    cout << "Stock: " << product->getQuantity() << "\n";
    cout << "Reorder level: " << product->getReorderLevel() << "\n";
    cout << "Status: " << (product->isLowStock() ? "LOW STOCK" : "OK") << "\n";
}

void showLowStock(const Inventory& inventory) {
    auto lowStock = inventory.getLowStockProducts();

    if (lowStock.empty()) {
        cout << "\nNo low-stock products.\n";
        return;
    }

    cout << "\n========== LOW STOCK REPORT ==========\n";
    cout << left
         << setw(8) << "ID"
         << setw(24) << "Name"
         << setw(12) << "Price"
         << setw(10) << "Stock"
         << setw(12) << "Reorder\n";

    for (const auto& product : lowStock) {
        cout << left
             << setw(8) << product.getId()
             << setw(24) << product.getName().substr(0, 22)
             << setw(12) << fixed << setprecision(2) << product.getPrice()
             << setw(10) << product.getQuantity()
             << setw(12) << product.getReorderLevel()
             << "\n";
    }
}

void generateBill(Inventory& inventory) {
    Billing billing;

    cout << "\n========== GENERATE BILL ==========\n";

    while (true) {
        int id = Utils::readInt("Product ID (0 to finish): ", 0, 999999);

        if (id == 0) break;

        int quantity = Utils::readInt("Quantity: ", 1, 1000000);

        if (billing.addItem(inventory, id, quantity)) {
            cout << "Item added to bill.\n";
        } else {
            cout << "Unable to add item. Check product ID and stock.\n";
        }
    }

    if (billing.isEmpty()) {
        cout << "No items added. Bill cancelled.\n";
        return;
    }

    billing.printBill();

    int save = Utils::readInt("Save bill? (1=Yes, 0=No): ", 0, 1);

    if (save == 1) {
        if (billing.saveBill()) {
            cout << "Bill saved in the data folder.\n";
        } else {
            cout << "Could not save bill.\n";
        }
    }
}

void showMenu() {
    cout << "\n\n==============================================\n";
    cout << "       SMART INVENTORY & BILLING SYSTEM       \n";
    cout << "==============================================\n";
    cout << "1. Add Product\n";
    cout << "2. Update Product\n";
    cout << "3. Delete Product\n";
    cout << "4. Search Product\n";
    cout << "5. View All Products\n";
    cout << "6. Generate Bill\n";
    cout << "7. Low Stock Report\n";
    cout << "8. Exit\n";
    cout << "==============================================\n";
}

int main() {
    Inventory inventory("data/products.csv");
    inventory.load();

    while (true) {
        showMenu();

        int choice = Utils::readInt("Enter choice: ", 1, 8);

        switch (choice) {
            case 1:
                addProduct(inventory);
                break;
            case 2:
                updateProduct(inventory);
                break;
            case 3:
                deleteProduct(inventory);
                break;
            case 4:
                searchProduct(inventory);
                break;
            case 5:
                displayProducts(inventory);
                break;
            case 6:
                generateBill(inventory);
                break;
            case 7:
                showLowStock(inventory);
                break;
            case 8:
                cout << "\nThank you for using the system!\n";
                return 0;
        }

        Utils::pause();
    }
}

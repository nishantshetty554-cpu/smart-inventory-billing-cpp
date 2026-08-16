#include "Inventory.h"
#include <fstream>
#include <sstream>

Inventory::Inventory(const std::string& filename)
    : filename(filename) {}

bool Inventory::load() {
    products.clear();

    std::ifstream file(filename);
    if (!file) {
        return false;
    }

    std::string line;
    std::getline(file, line); // header

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string field;
        int id, quantity, reorderLevel;
        double price;
        std::string name;

        try {
            std::getline(ss, field, ',');
            id = std::stoi(field);

            std::getline(ss, name, ',');

            std::getline(ss, field, ',');
            price = std::stod(field);

            std::getline(ss, field, ',');
            quantity = std::stoi(field);

            std::getline(ss, field, ',');
            reorderLevel = std::stoi(field);

            products.emplace_back(id, name, price, quantity, reorderLevel);
        } catch (...) {
            // Ignore malformed rows.
        }
    }

    return true;
}

bool Inventory::save() const {
    std::ofstream file(filename);
    if (!file) return false;

    file << "id,name,price,quantity,reorderLevel\n";
    for (const auto& product : products) {
        file << product.getId() << ","
             << product.getName() << ","
             << product.getPrice() << ","
             << product.getQuantity() << ","
             << product.getReorderLevel() << "\n";
    }
    return true;
}

bool Inventory::addProduct(const Product& product) {
    if (findProduct(product.getId()) != nullptr) return false;
    if (product.getId() <= 0 || product.getPrice() < 0 ||
        product.getQuantity() < 0 || product.getReorderLevel() < 0 ||
        product.getName().empty()) {
        return false;
    }

    products.push_back(product);
    return save();
}

bool Inventory::updateProduct(int id, const std::string& name, double price,
                              int quantity, int reorderLevel) {
    Product* product = findProduct(id);
    if (!product || name.empty() || price < 0 || quantity < 0 || reorderLevel < 0) {
        return false;
    }

    product->setName(name);
    product->setPrice(price);
    product->setQuantity(quantity);
    product->setReorderLevel(reorderLevel);
    return save();
}

bool Inventory::deleteProduct(int id) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getId() == id) {
            products.erase(it);
            return save();
        }
    }
    return false;
}

Product* Inventory::findProduct(int id) {
    for (auto& product : products) {
        if (product.getId() == id) return &product;
    }
    return nullptr;
}

const Product* Inventory::findProduct(int id) const {
    for (const auto& product : products) {
        if (product.getId() == id) return &product;
    }
    return nullptr;
}

const std::vector<Product>& Inventory::getProducts() const {
    return products;
}

std::vector<Product> Inventory::getLowStockProducts() const {
    std::vector<Product> result;
    for (const auto& product : products) {
        if (product.isLowStock()) result.push_back(product);
    }
    return result;
}

#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "Product.h"

class Inventory {
private:
    std::vector<Product> products;
    std::string filename;

public:
    explicit Inventory(const std::string& filename = "data/products.csv");

    bool load();
    bool save() const;

    bool addProduct(const Product& product);
    bool updateProduct(int id, const std::string& name, double price,
                       int quantity, int reorderLevel);
    bool deleteProduct(int id);

    Product* findProduct(int id);
    const Product* findProduct(int id) const;

    const std::vector<Product>& getProducts() const;
    std::vector<Product> getLowStockProducts() const;
};
#endif

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    double price;
    int quantity;
    int reorderLevel;

public:
    Product();
    Product(int id, const std::string& name, double price, int quantity, int reorderLevel);

    int getId() const;
    const std::string& getName() const;
    double getPrice() const;
    int getQuantity() const;
    int getReorderLevel() const;

    void setName(const std::string& name);
    void setPrice(double price);
    void setQuantity(int quantity);
    void setReorderLevel(int level);

    bool isLowStock() const;
};
#endif

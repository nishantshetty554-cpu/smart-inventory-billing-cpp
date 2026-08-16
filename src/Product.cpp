#include "Product.h"

Product::Product()
    : id(0), name(""), price(0.0), quantity(0), reorderLevel(5) {}

Product::Product(int id, const std::string& name, double price, int quantity, int reorderLevel)
    : id(id), name(name), price(price), quantity(quantity), reorderLevel(reorderLevel) {}

int Product::getId() const { return id; }
const std::string& Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }
int Product::getReorderLevel() const { return reorderLevel; }

void Product::setName(const std::string& value) { name = value; }
void Product::setPrice(double value) { price = value; }
void Product::setQuantity(int value) { quantity = value; }
void Product::setReorderLevel(int value) { reorderLevel = value; }

bool Product::isLowStock() const {
    return quantity <= reorderLevel;
}

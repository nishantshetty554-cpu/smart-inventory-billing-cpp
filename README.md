# Smart Inventory & Billing Management System

A beginner-friendly C++ console application designed as a software-engineering portfolio project.

## Features

- Product creation
- Product update
- Product deletion
- Product search
- Inventory listing
- Low-stock detection
- Customer bill generation
- 18% GST calculation
- Stock deduction after billing
- Bill text-file generation
- CSV-based data persistence
- Input validation

## Technology

- C++
- Object-Oriented Programming
- STL vector
- File handling
- Modular programming
- Basic software testing

## Project Structure

```text
smart-inventory-billing-cpp/
├── include/
│   ├── Product.h
│   ├── Inventory.h
│   ├── Billing.h
│   └── Utils.h
├── src/
│   ├── Product.cpp
│   ├── Inventory.cpp
│   ├── Billing.cpp
│   ├── Utils.cpp
│   └── main.cpp
├── data/
│   └── products.csv
├── tests/
│   └── test_cases.txt
├── docs/
├── screenshots/
├── README.md
└── .gitignore
```

## How to Compile

From the project root:

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o inventory_app
```

## How to Run

Linux/macOS:

```bash
./inventory_app
```

Windows:

```bash
inventory_app.exe
```

## Main Modules

### Product
Stores product ID, name, price, quantity and reorder level.

### Inventory
Manages products using `std::vector`, including add, update, delete, search and persistence.

### Billing
Creates bills, calculates subtotal/GST/total and reduces stock after a successful purchase.

### Utils
Handles safe console input.

## OOP Concepts Demonstrated

- Classes and objects
- Encapsulation
- Constructors
- Access specifiers
- Member functions
- Composition
- `const` member functions
- STL containers

## Example Use Case

A small shop can maintain products and stock, search products, generate a customer bill and automatically reduce inventory after a sale.

## Future Enhancements

- MySQL database
- User login and role-based access
- Sales history database
- GUI/web interface
- PDF invoice
- Product categories
- CSV import/export
- Automated unit testing
- REST API integration

## Disclaimer

This is an educational software project. It is not intended for production financial or inventory systems without additional security, concurrency, auditing and database controls.

#include "Utils.h"
#include <iostream>
#include <limits>

namespace Utils {

std::string readNonEmptyString(const std::string& prompt) {
    std::string value;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);

        if (!value.empty()) return value;
        std::cout << "Input cannot be empty. Try again.\n";
    }
}

int readInt(const std::string& prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;

        if (std::cin >> value && value >= minValue && value <= maxValue) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Invalid input. Enter a value from "
                  << minValue << " to " << maxValue << ".\n";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double readDouble(const std::string& prompt, double minValue) {
    double value;

    while (true) {
        std::cout << prompt;

        if (std::cin >> value && value >= minValue) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Invalid input. Try again.\n";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

}

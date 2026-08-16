#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
    std::string readNonEmptyString(const std::string& prompt);
    int readInt(const std::string& prompt, int minValue, int maxValue);
    double readDouble(const std::string& prompt, double minValue);
    void pause();
}
#endif

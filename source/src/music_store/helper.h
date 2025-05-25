#pragma once
#include <string>

inline int toInt(std::string str) {
    int result = 0;
    for (const char &c: str) {
        if (c < '0' || c > '9') {
            throw std::invalid_argument("Invalid integer string");
        }
        result = result * 10 + (c - '0');
    }
    return result;
}

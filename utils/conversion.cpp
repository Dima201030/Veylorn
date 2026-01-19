#include "conversion.h"

std::string toString(ErrorsCodeMap err) {
    switch (err) {
    case ErrorsCodeMap::OK:
        return "OK";
    case ErrorsCodeMap::NOFILE:
        return "NOFILE";
    case ErrorsCodeMap::NOAVAILABLE:
        return "NOAVAILABLE";
    default:
        return "UNKNOWN";
    }
}

int toInt(ErrorsCodeMap err) {
    switch (err) {
    case ErrorsCodeMap::OK:
        return 0;
    case ErrorsCodeMap::NOFILE:
        return 1;
    case ErrorsCodeMap::NOAVAILABLE:
        return 2;
    default:
        return -1;
    }
}

int toInt(size_t value) {
    return static_cast<int>(value);
}

size_t toST(int value) {
    return static_cast<size_t>(value);
}




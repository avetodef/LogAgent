#pragma once
#include <string>

class Log {
public:
    int id;
    std::string timestamp;
    std::string level;
    std::string module;
    std::string message;

    static Log fromString(const std::string& line);
    std::string toString() const;
};

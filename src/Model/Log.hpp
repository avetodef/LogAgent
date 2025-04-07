#pragma once

#include <string>
#include <sstream>

class Log {
public:
    int id;
    std::string timestamp;
    std::string level;
    std::string module;
    std::string message;

    Log() = default;
    Log(int id, const std::string& timestamp, const std::string& level, const std::string& module, const std::string& message);

    std::string toString() const;
    static Log fromString(const std::string& line);
};

#include "Log.hpp"
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdexcept>

static std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Log Log::fromString(const std::string& line) {
    std::vector<std::string> parts = split(line, '|');
    if (parts.size() < 4) {
        throw std::runtime_error("Invalid log format");
    }

    Log log;
    log.timestamp = parts[0];
    log.level = parts[1];
    log.module = parts[2];
    log.message = parts[3];

    for (auto& field : { &log.timestamp, &log.level, &log.module, &log.message }) {
        size_t start = field->find_first_not_of(" \t");
        size_t end = field->find_last_not_of(" \t");
        if (start != std::string::npos && end != std::string::npos)
            *field = field->substr(start, end - start + 1);
    }

    return log;
}

std::string Log::toString() const {
    std::ostringstream oss;
    oss << timestamp << " | " << level << " | " << module << " | " << message;
    return oss.str();
}

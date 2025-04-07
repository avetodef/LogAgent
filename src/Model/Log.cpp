#include "Log.hpp"

Log::Log(int id, const std::string& timestamp, const std::string& level, const std::string& module, const std::string& message)
        : id(id), timestamp(timestamp), level(level), module(module), message(message) {}

std::string Log::toString() const {
    return std::to_string(id) + "|" + timestamp + "|" + level + "|" + module + "|" + message;
}

Log Log::fromString(const std::string& line) {
    std::istringstream iss(line);
    std::string token;

    Log log;

    std::getline(iss, token, '|');
    log.id = std::stoi(token);

    std::getline(iss, log.timestamp, '|');
    std::getline(iss, log.level, '|');
    std::getline(iss, log.module, '|');
    std::getline(iss, log.message);

    return log;
}

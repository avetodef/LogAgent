#include "InMemoryRepository.hpp"
#include <algorithm>
#include <iostream>

void InMemoryRepository::save(const Log &log) {
    //std::lock_guard<std::mutex> lock(mutex);
    logs.push_back(log);
}

std::optional<Log> InMemoryRepository::findById(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    for (const auto &log: logs) {
        if (log.id == id) return log;
    }
    return std::nullopt;
}

void InMemoryRepository::deleteById(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    logs.erase(std::remove_if(logs.begin(), logs.end(), [id](const Log &log) {
        return log.id == id;
    }), logs.end());
}

void InMemoryRepository::setLogs(const std::vector<Log> &newLogs) {
    std::lock_guard<std::mutex> lock(mutex);
    logs = newLogs;
}

std::vector<Log> InMemoryRepository::query(
        std::optional<std::chrono::system_clock::time_point> start,
        std::optional<std::chrono::system_clock::time_point> end,
        std::optional<std::string> module,
        std::optional<std::string> method,
        std::optional<LogLevel> level
) const {
    std::vector<Log> result;

    for (const auto &log: logs) {
        if (start.has_value() && log.timestamp < *start) continue;
        if (end.has_value() && log.timestamp >= *end) continue;
        if (module.has_value() && log.module != *module) continue;
        if (method.has_value() && log.method != *method) continue;
        if (level.has_value() && log.level != *level) continue;
        result.push_back(log);
    }

    return result;
}

void InMemoryRepository::clear() {
    logs.clear();
}

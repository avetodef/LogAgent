#include <optional>
#include <vector>
#include "Model/Log.hpp"
#include <memory>

#pragma once

class LogRepository {
public:
    virtual ~LogRepository() = default;
    LogRepository() {}

    std::vector<Log> logs;

    virtual std::optional<Log> findById(int id) = 0;
    virtual void save(const Log& log) = 0;
    virtual void deleteById(int id) = 0;
    virtual void setLogs(const std::vector<Log>& logs) = 0;
    virtual void clear() = 0;
    virtual std::vector<Log> query(
            std::optional<std::chrono::system_clock::time_point> start,
            std::optional<std::chrono::system_clock::time_point> end,
            std::optional<std::string> module,
            std::optional<std::string> method,
            std::optional<LogLevel> level
    ) const = 0;
};

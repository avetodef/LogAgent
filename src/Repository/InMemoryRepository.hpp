#pragma once

#include "LogRepository.hpp"
#include "Model/Log.hpp"
#include <vector>
#include <mutex>

class InMemoryRepository : public LogRepository {
private:
    mutable std::mutex mutex;

public:
    void save(const Log& log) override;

    std::optional<Log> findById(int id) override;
    void deleteById(int id) override;
    void setLogs(const std::vector<Log>& logs) override;
    void clear() override;
    std::vector<Log> query(
            std::optional<std::chrono::system_clock::time_point> start,
            std::optional<std::chrono::system_clock::time_point> end,
            std::optional<std::string> module,
            std::optional<std::string> method,
            std::optional<LogLevel> level
    ) const override;
};

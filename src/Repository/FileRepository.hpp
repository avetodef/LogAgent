#pragma once

#include "LogRepository.hpp"
#include "../Model/Log.hpp"
#include <vector>
#include <fstream>
#include <memory>
#include <mutex>

class FileRepository : public LogRepository {
private:
    std::string filename;
    mutable std::mutex fileMutex;

public:
    explicit FileRepository(const std::string& filename);

    void save(const Log& log) override;
    std::optional<Log> findById(int id) override;
    void deleteById(int id) override;
    std::vector<Log> query(
            std::optional<std::chrono::system_clock::time_point> start,
            std::optional<std::chrono::system_clock::time_point> end,
            std::optional<std::string> module,
            std::optional<std::string> method,
            std::optional<LogLevel> level
    ) const override;
    void clear() override;
};

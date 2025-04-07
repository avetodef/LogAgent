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
    std::vector<Log> findAllByCriteria(const std::vector<std::shared_ptr<Criteria>>& criteria) override;
    void setLogs(const std::vector<Log>& logs) override;
};

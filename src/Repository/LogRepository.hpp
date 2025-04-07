#include <optional>
#include <vector>
#include "Model/Log.hpp"
#include "Criteria/Criteria.hpp"
#include <memory>

#pragma once

class LogRepository {
public:
    virtual ~LogRepository() = default;
    LogRepository() {}

    std::vector<Log> logs;

    virtual std::optional<Log> findById(int id) = 0;
    virtual std::vector<Log> findAllByCriteria(const std::vector<std::shared_ptr<Criteria>>& criteria) = 0;
    virtual void save(const Log& log) = 0;
    virtual void deleteById(int id) = 0;
    virtual void setLogs(const std::vector<Log>& logs) = 0;
};

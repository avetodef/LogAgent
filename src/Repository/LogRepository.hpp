#include <optional>
#include "Log.hpp"
#include <vector>
#include "Criteria.hpp"
#include <memory>

#pragma once

class LogRepository {
public:
    virtual ~LogRepository() = default;
    LogRepository() {}

    virtual std::optional<Log> findById(int id) = 0;
    virtual std::vector<Log> findAllByCriteria(const std::vector<std::shared_ptr<Criteria>>& criteria) = 0;
    virtual void save(const Log& log) = 0;
    virtual void deleteById(int id) = 0;
};

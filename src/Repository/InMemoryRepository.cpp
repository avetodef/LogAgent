#include "InMemoryRepository.hpp"
#include <algorithm>

void InMemoryRepository::save(const Log& log) {
    std::lock_guard<std::mutex> lock(mutex);
    logs.push_back(log);
}

std::optional<Log> InMemoryRepository::findById(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    for (const auto& log : logs) {
        if (log.id == id) return log;
    }
    return std::nullopt;
}

void InMemoryRepository::deleteById(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    logs.erase(std::remove_if(logs.begin(), logs.end(), [id](const Log& log) {
        return log.id == id;
    }), logs.end());
}

std::vector<Log> InMemoryRepository::findAllByCriteria(const std::vector<std::shared_ptr<Criteria>>& criterias) {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<Log> result;
    for (const auto& log : logs) {
        for (const auto & criteria : criterias){
            if (criteria->isSatisfiedBy(log)) {
                result.push_back(log);
            }
        }
    }
    return result;
}

void InMemoryRepository::setLogs(const std::vector<Log>& newLogs) {
    std::lock_guard<std::mutex> lock(mutex);
    logs = newLogs;
}

#pragma once

#include "LogRepository.hpp"
#include "../Model/Log.hpp"
#include "../Criteria/Criteria.hpp"
#include <vector>
#include <fstream>
#include <memory>
#include <mutex>

class FileRepository : public LogRepository {
private:
    std::string filename;
    mutable std::mutex fileMutex;

    int generateId() const;

public:
    explicit FileRepository(const std::string& filename);

    void save(const Log& log) override;
    std::optional<Log> findById(int id) override;
    void deleteById(int id) override;
    std::vector<Log> findAllByCriteria(const std::vector<std::shared_ptr<Criteria>>& criteria) override;
};

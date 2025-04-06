// FileRepository.hpp
#pragma once
#include "LogRepository.hpp"
#include <string>
#include <vector>
#include <fstream>

class FileRepository : public LogRepository {
private:
    std::string filepath;
    std::vector<Log> cache;
    void loadFromFile();
    void saveToFile();

public:
    explicit FileRepository(const std::string& filepath);
    std::optional<Log> findById(int id) override;
    Log save(const Log& log) override;
    void deleteById(int id) override;
    std::vector<Log> findAllByCriteria(const Criteria& criteria) override;
};

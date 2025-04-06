#include "FileRepository.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

FileRepository::FileRepository(const std::string& filepath) : filepath(filepath) {}

std::optional<Log> FileRepository::findById(int id) {
    std::ifstream file(filepath);
    std::string line;
    while (std::getline(file, line)) {
        Log log = Log::fromString(line);
        if (log.id == id) {
            return log;
        }
    }
    return std::nullopt;
}

Log FileRepository::save(const Log& log) {
    std::ofstream file(filepath, std::ios::app);
    file << log.toString() << std::endl;
    return log;
}

void FileRepository::deleteById(int id) {
    std::ifstream inFile(filepath);
    std::ofstream outFile("temp.txt");

    std::string line;
    while (std::getline(inFile, line)) {
        Log log = Log::fromString(line);
        if (log.id != id) {
            outFile << log.toString() << std::endl;
        }
    }

    inFile.close();
    outFile.close();

    std::remove(filepath.c_str());
    std::rename("temp.txt", filepath.c_str());
}

std::vector<Log> FileRepository::findAllByCriteria(const std::shared_ptr<Criteria>& criteria) {
    std::vector<Log> result;
    std::ifstream file(filepath);
    std::string line;
    while (std::getline(file, line)) {
        Log log = Log::fromString(line);
        if (criteria->isSatisfiedBy(log)) {
            result.push_back(log);
        }
    }
    return result;
}

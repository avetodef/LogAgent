#include "FileRepository.hpp"
#include <filesystem>

FileRepository::FileRepository(const std::string& filename) : filename(filename) {}

int FileRepository::generateId() const {
    std::ifstream in(filename);
    std::string line;
    int maxId = 0;

    while (std::getline(in, line)) {
        Log log = Log::fromString(line);
        if (log.id > maxId)
            maxId = log.id;
    }

    return maxId + 1;
}

void FileRepository::save(const Log& inputLog) {
    std::lock_guard<std::mutex> lock(fileMutex);
    Log log = inputLog;

    if (log.id == -1) {
        log.id = generateId();
    }

    std::ofstream out(filename, std::ios::app);
    out << log.toString() << "\n";
}

std::optional<Log> FileRepository::findById(int id) {
    std::lock_guard<std::mutex> lock(fileMutex);
    std::ifstream in(filename);
    std::string line;

    while (std::getline(in, line)) {
        Log log = Log::fromString(line);
        if (log.id == id) {
            return log;
        }
    }

    return std::nullopt;
}

void FileRepository::deleteById(int id) {
    std::lock_guard<std::mutex> lock(fileMutex);
    std::ifstream in(filename);
    std::ofstream temp("temp.txt");

    std::string line;
    while (std::getline(in, line)) {
        Log log = Log::fromString(line);
        if (log.id != id) {
            temp << line << "\n";
        }
    }

    in.close();
    temp.close();
    std::filesystem::remove(filename);
    std::filesystem::rename("temp.txt", filename);
}

std::vector<Log> FileRepository::findAllByCriteria(const std::vector<std::shared_ptr<Criteria>>& criterias) {
    std::lock_guard<std::mutex> lock(fileMutex);
    std::ifstream in(filename);
    std::vector<Log> result;
    std::string line;

    while (std::getline(in, line)) {
        Log log = Log::fromString(line);
        for (const auto & criteria : criterias){
            if (criteria->isSatisfiedBy(log)) {
                result.push_back(log);
            }
        }
    }

    return result;
}

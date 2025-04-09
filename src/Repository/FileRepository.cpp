#include "FileRepository.hpp"
#include <filesystem>

FileRepository::FileRepository(const std::string& filename) : filename(filename) {}

//int FileRepository::generateId() const {
//    std::ifstream in(filename);
//    std::string line;
//    int maxId = 0;
//
//    while (std::getline(in, line)) {
//        Log log = Log::fromString(line);
//        if (log.id > maxId)
//            maxId = log.id;
//    }
//
//    return maxId + 1;
//}

void FileRepository::save(const Log& inputLog) {
    std::lock_guard<std::mutex> lock(fileMutex);
    Log log = inputLog;
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

std::vector<Log> FileRepository::query(std::optional<std::chrono::system_clock::time_point> start,
                                       std::optional<std::chrono::system_clock::time_point> end,
                                       std::optional<std::string> module, std::optional<std::string> method,
                                       std::optional<LogLevel> level) const {
    return std::vector<Log>();
}

void FileRepository::clear() {

}

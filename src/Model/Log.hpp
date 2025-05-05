#pragma once
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    UNKNOWN
};

class Log {
public:
    int id;
    std::chrono::system_clock::time_point timestamp;
    LogLevel level;
    std::string module;
    std::string method;
    std::string message;

    Log() = default;

    Log(int id, const std::chrono::system_clock::time_point& timestamp,
        LogLevel level, const std::string& module,
        const std::string& method, const std::string& message)
            : id(id), timestamp(timestamp), level(level),
              module(module), method(method), message(message) {}

    std::string toString() const {
        std::time_t t = std::chrono::system_clock::to_time_t(timestamp);
        std::tm tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << id << "|"
            << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "|"
            << logLevelToString(level) << "|"
            << module << "|"
            << method << "|"
            << message;
        return oss.str();
    }

    static Log fromString(const std::string& line) {
        std::istringstream iss(line);
        char delimiter;
        int id;
        std::string timestampStr, levelStr, module, message;

        // Чтение id
        iss >> id >> delimiter;

        // Чтение остальных полей
        std::getline(iss, timestampStr, '|');
        std::getline(iss, levelStr, '|');
        std::getline(iss, module, '|');
        std::getline(iss, message); // Всё, что осталось — message

        // Убрать пробелы в начале/конце (опционально)
        message.erase(0, message.find_first_not_of(" \t"));
        message.erase(message.find_last_not_of(" \t") + 1);

        // Парсинг времени
        std::tm tm = {};
        std::istringstream tsStream(timestampStr);
        tsStream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        auto timestamp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

        return Log(id, timestamp, stringToLogLevel(levelStr), module, "", message);
    }

    static LogLevel stringToLogLevel(const std::string& s) {
        if (s == "TRACE") return LogLevel::TRACE;
        if (s == "DEBUG") return LogLevel::DEBUG;
        if (s == "INFO") return LogLevel::INFO;
        if (s == "WARN") return LogLevel::WARN;
        if (s == "ERROR") return LogLevel::ERROR;
        return LogLevel::UNKNOWN;
    }

    static std::string logLevelToString(LogLevel level) {
        switch (level) {
            case LogLevel::TRACE: return "TRACE";
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARN: return "WARN";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

};
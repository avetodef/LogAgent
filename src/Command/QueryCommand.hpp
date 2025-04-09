#pragma once
#include "Command.hpp"
#include "Repository/LogRepository.hpp"
#include "Model/Log.hpp"
#include <iostream>
#include <vector>
#include <optional>
#include <iomanip>
#include <ctime>
#include <cstring>

class QueryCommand : public Command {
public:
    QueryCommand(std::string args, std::shared_ptr<LogRepository> repository)
            : args(std::move(args)), repository(std::move(repository)) {}

    void execute() override {
        //std::cout << "[QueryCommand] Executing query command with args: " << args << "\n";
        try {
            auto filters = parseFilters();

            if (!hasValidFilters(filters)) {
                //std::cout << "[QueryCommand] No valid filters provided. Showing help.\n";
                printHelp();
                return;
            }

            //std::cout << "[QueryCommand] Querying repository with provided filters...\n";
            auto logs = repository->query(
                    filters.start,
                    filters.end,
                    filters.module,
                    filters.method,
                    filters.level
            );

            //std::cout << "[QueryCommand] Query returned " << logs.size() << " results.\n";
            printResults(logs);

        } catch (const std::exception& e) {
            std::cerr << "[QueryCommand] Query error: " << e.what() << "\n";
        }
    }

private:
    struct QueryFilters {
        std::optional<std::chrono::system_clock::time_point> start;
        std::optional<std::chrono::system_clock::time_point> end;
        std::optional<std::string> module;
        std::optional<std::string> method;
        std::optional<LogLevel> level;
    };

    std::string args;
    std::shared_ptr<LogRepository> repository;

    bool hasValidFilters(const QueryFilters& filters) const {
        return filters.start || filters.end || filters.module || filters.method || filters.level;
    }

    void printHelp() const {
        std::cout << "Usage: query [start=TIME] [end=TIME] [module=NAME] [method=NAME] [level=LEVEL]\n"
                  << "Time formats: YYYY-MM-DD, YYYY-MM-DD HH:MM, YYYY-MM-DD HH:MM:SS\n"
                  << "Example: query start=\"2023-06-15 08:30\" end=\"2023-06-15 09:00\" level=ERROR\n";
    }

    QueryFilters parseFilters() const {
        QueryFilters filters;
        std::vector<std::string> tokens;
        std::string current;
        bool inQuotes = false;

        //std::cout << "[QueryCommand] Parsing filters from args...\n";
        for (char c : args) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ' ' && !inQuotes) {
                if (!current.empty()) {
                    tokens.push_back(current);
                    current.clear();
                }
            } else {
                current += c;
            }
        }
        if (!current.empty()) tokens.push_back(current);

        for (const auto& token : tokens) {
            size_t eq_pos = token.find('=');
            if (eq_pos == std::string::npos) continue;

            std::string key = token.substr(0, eq_pos);
            std::string value = token.substr(eq_pos + 1);

            //std::cout << "[QueryCommand] Parsed token: " << key << " = " << value << "\n";

            if (key == "start") filters.start = parseTime(value, false);
            else if (key == "end") filters.end = parseTime(value, true);
            else if (key == "module") filters.module = value;
            else if (key == "method") filters.method = value;
            else if (key == "level") filters.level = Log::stringToLogLevel(value);
        }

        return filters;
    }

    std::chrono::system_clock::time_point parseTime(const std::string& timeStr, bool isEnd) const {
        std::tm tm = {};
        std::istringstream ss(timeStr);
        const char* formats[] = {
                "%Y-%m-%d %H:%M:%S",
                "%Y-%m-%d %H:%M",
                "%Y-%m-%d"
        };

        //std::cout << "[QueryCommand] Parsing time string: \"" << timeStr << "\"\n";

        for (const auto& fmt : formats) {
            ss.clear();
            ss.str(timeStr);
            ss >> std::get_time(&tm, fmt);

            if (!ss.fail()) {
                if (strcmp(fmt, "%Y-%m-%d %H:%M") == 0) {
                    tm.tm_sec = isEnd ? 59 : 0;
                }
                tm.tm_isdst = -1;
                auto time = std::mktime(&tm);
                //std::cout << "[QueryCommand] Time parsed successfully using format: " << fmt << "\n";
                return std::chrono::system_clock::from_time_t(time);
            }
        }

        throw std::runtime_error("Invalid time format: " + timeStr);
    }

    void printResults(const std::vector<Log>& logs) const {
        if (logs.empty()) {
            std::cout << "No logs found matching the criteria\n";
            return;
        }

        //std::cout << "[QueryCommand] Printing query results:\n";
        for (const auto& log : logs) {
            std::time_t t = std::chrono::system_clock::to_time_t(log.timestamp);
            std::cout << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << " | "
                      << Log::logLevelToString(log.level) << " | "
                      << log.module << "::" << log.method << " | "
                      << log.message << "\n";
        }
        std::cout << "Found " << logs.size() << " matching logs\n";
    }
};

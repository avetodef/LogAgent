#pragma once
#include "Command.hpp"
#include "LogLevel.hpp"
#include "LogRepository.hpp"
#include "LogLevelCriteria.hpp"
#include "LogModuleCriteria.hpp"
#include "LogMethodCriteria.hpp"
#include <sstream>
#include <iostream>

class QueryCommand : public Command {
private:
    std::string input;
    std::shared_ptr<LogRepository> repository;

public:
    QueryCommand(const std::string& input, std::shared_ptr<LogRepository> repo)
            : input(input), repository(std::move(repo)) {}

    void execute() override {
        std::istringstream iss(input);
        std::string word;
        std::vector<std::shared_ptr<Criteria>> criteria;

        // Пропускаем слово "query"
        iss >> word;

        while (iss >> word) {
            auto pos = word.find('=');
            if (pos != std::string::npos) {
                std::string key = word.substr(0, pos);
                std::string value = word.substr(pos + 1);

                if (key == "level") {
                    LogLevel lvl;
                    if (value == "INFO") lvl = LogLevel::INFO;
                    else if (value == "ERROR") lvl = LogLevel::ERROR;
                    else if (value == "WARN") lvl = LogLevel::WARN;
                    else if (value == "DEBUG") lvl = LogLevel::DEBUG;
                    else if (value == "TRACE") lvl = LogLevel::TRACE;
                    else continue; // unknown level

                    criteria.push_back(std::make_shared<LogLevelCriteria>(lvl));
                }
                else if (key == "module") {
                    criteria.push_back(std::make_shared<LogModuleCriteria>(value));
                }
                else if (key == "method") {
                    criteria.push_back(std::make_shared<LogMethodCriteria>(value));
                }
            }
        }

        auto logs = repository->findAllByCriteria(criteria);

        if (logs.empty()) {
            std::cout << "No logs found by these criterias.\n";
        } else {
            std::cout << "Found logs: " << logs.size() << "\n\n";
            for (const auto& log : logs) {
                std::cout << log.toString() << "\n";
            }
        }
    }
};

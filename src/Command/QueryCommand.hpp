#pragma once
#include "Command.hpp"
#include "Repository/LogRepository.hpp"
#include <iostream>
#include <map>
#include <sstream>

class QueryCommand : public Command {
public:
    QueryCommand(const std::string &args, const std::shared_ptr<LogRepository> &repository) : args(args),
                                                                                              repository(repository) {}

    void execute() override {
        std::map<std::string, std::string> filters;
        std::istringstream iss(args);
        std::string token;

        while (iss >> token) {
            auto pos = token.find('=');
            if (pos != std::string::npos) {
                filters[token.substr(0, pos)] = token.substr(pos + 1);
            }
        }

        for (const auto& log : repository->logs) {
            if (!filters["start"].empty() && log.timestamp < filters["start"]) continue;
            if (!filters["end"].empty() && log.timestamp > filters["end"]) continue;
            if (!filters["module"].empty() && log.module != filters["module"]) continue;
            if (!filters["method"].empty() && log.method != filters["method"]) continue;
            if (!filters["level"].empty() && log.level != filters["level"]) continue;

            std::cout << log.timestamp << " " << log.module << " " << log.method
                      << " " << log.level << " " << log.message << "\n";
        }
    }

private:
    std::string args;
    std::shared_ptr<LogRepository> repository;
};

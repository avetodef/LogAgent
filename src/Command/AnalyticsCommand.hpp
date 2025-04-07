#pragma once
#include "Command.hpp"
#include <iostream>
#include <map>
#include <utility>

class AnalyticsCommand : public Command {
public:
    explicit AnalyticsCommand(std::shared_ptr<LogRepository> repository) : repository(std::move(repository)) {}

    void execute() override {
        int warnings = 0, errors = 0;
        std::map<std::string, int> errorTypes;
        std::map<std::string, int> moduleErrors;

        for (const auto& log : repository->logs) {
            if (log.level == "WARNING") warnings++;
            if (log.level == "ERROR") {
                errors++;
                errorTypes[log.message]++;
                moduleErrors[log.module]++;
            }
        }

        std::cout << "Amount of warnings: " << warnings << "\n";
        std::cout << "Amounf of errors: " << errors << "\n";

        std::cout << "Error counts:\n";
        for (const auto& [type, count] : errorTypes) {
            std::cout << "- " << type << ": " << count << "\n";
        }

        std::string mostFailingModule;
        int maxErrors = 0;
        for (const auto& [mod, count] : moduleErrors) {
            if (count > maxErrors) {
                mostFailingModule = mod;
                maxErrors = count;
            }
        }

        std::cout << "Most failing module: " << mostFailingModule << " (" << maxErrors << ")\n";
    }
private:
    std::shared_ptr<LogRepository> repository;
};

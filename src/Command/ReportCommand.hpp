#pragma once
#include "Command.hpp"
#include <fstream>
#include <iostream>
#include <map>

class ReportCommand : public Command {
public:
    explicit ReportCommand(const std::shared_ptr<LogRepository> &repository) : repository(repository) {}

    void execute() override {
        std::ofstream out("report.txt");
        if (!out.is_open()) {
            std::cout << "Ошибка записи файла.\n";
            return;
        }

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

        out << "Amount of warnings: " << warnings << "\n";
        out << "Amount of errors: " << errors << "\n";

        out << "Error count:\n";
        for (const auto& [type, count] : errorTypes) {
            out << "- " << type << ": " << count << "\n";
        }

        std::string mostFailingModule;
        int maxErrors = 0;
        for (const auto& [mod, count] : moduleErrors) {
            if (count > maxErrors) {
                mostFailingModule = mod;
                maxErrors = count;
            }
        }

        out << "Most failing module: " << mostFailingModule << " (" << maxErrors << ")\n";

        out.close();
        std::cout << "Log analysis is saved in report.txt\n";
    }

private:
    std::shared_ptr<LogRepository> repository;
};

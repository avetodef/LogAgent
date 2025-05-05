#pragma once
#include "Command.hpp"
#include <iostream>
#include <map>
#include <set>
#include <iomanip>
#include <ctime>
#include <chrono>

class AnalyticsCommand : public Command {
public:
    explicit AnalyticsCommand(std::shared_ptr<LogRepository> repository)
            : repository(std::move(repository)) {}

    void execute() override {
        system("chcp 65001");
        std::locale::global(std::locale(""));
        std::cout.imbue(std::locale());

        int warnings = 0, errors = 0, securityErrors = 0;
        std::map<std::string, int> errorTypes;
        std::map<std::string, int> moduleErrors;
        std::map<std::string, int> subsystemErrors;
        std::map<int, int> hourErrorHistogram;
        std::set<std::string> uniqueErrorMessages;
        std::string mostRecentError;
        std::time_t latestTime = 0;

        for (const auto& log : repository->logs) {
            if (log.level == LogLevel::WARN) warnings++;
            if (log.level == LogLevel::ERROR) {
                errors++;
                if (!log.message.empty()) {
                    errorTypes[log.message]++;
                }
                moduleErrors[log.module]++;
                uniqueErrorMessages.insert(log.message);

                // Подсистема (например, RF::)
                auto subsystem = log.module.substr(0, log.module.find("::"));
                subsystemErrors[subsystem]++;

                // Ошибки по часам
                std::time_t t = std::chrono::system_clock::to_time_t(log.timestamp);
                std::tm local_tm = *std::localtime(&t);
                hourErrorHistogram[local_tm.tm_hour]++;

                // Безопасность
                if (log.message.find("SECURITY") != std::string::npos ||
                    log.message.find("TLS") != std::string::npos ||
                    log.message.find("CERTIFICATE") != std::string::npos)
                {
                    securityErrors++;
                }

                // Последняя ошибка
                if (t > latestTime) {
                    latestTime = t;
                    mostRecentError = log.message;
                }
            }
        }

        // === Вывод аналитики ===
        std::cout << "\n===== Log Analytics Report =====\n";
        std::cout << "Warnings: " << warnings << "\n";
        std::cout << "Errors: " << errors << "\n";
        std::cout << "Unique error types: " << uniqueErrorMessages.size() << "\n";
        std::cout << "Security-related errors: " << securityErrors << "\n\n";

        std::cout << "Top error types:\n";
        for (const auto& [type, count] : errorTypes) {
            std::cout << " - " << type << ": " << count << "\n";
        }

        std::string mostFailingModule;
        int maxErrors = 0;
        for (const auto& [mod, count] : moduleErrors) {
            if (count > maxErrors) {
                mostFailingModule = mod;
                maxErrors = count;
            }
        }
        std::cout << "\nMost failing module: " << mostFailingModule << " (" << maxErrors << " errors)\n";

        std::cout << "\nErrors by subsystem:\n";
        for (const auto& [subsystem, count] : subsystemErrors) {
            std::cout << " - " << subsystem << ": " << count << "\n";
        }

        std::cout << "\nError frequency by hour:\n";
        for (const auto& [hour, count] : hourErrorHistogram) {
            std::cout << " - " << std::setw(2) << std::setfill('0') << hour << ":00 — " << count << "\n";
        }

        std::cout << "\nMost recent error: " << mostRecentError << "\n";
        std::cout << "Occurred at: " << std::put_time(std::localtime(&latestTime), "%Y-%m-%d %H:%M:%S") << "\n";

        std::cout << "================================\n\n";
    }

private:
    std::shared_ptr<LogRepository> repository;
};
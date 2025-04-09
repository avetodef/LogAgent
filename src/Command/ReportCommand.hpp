#pragma once
#include "Command.hpp"
#include <fstream>
#include <map>
#include <set>
#include <iomanip>
#include <ctime>

class ReportCommand : public Command {
public:
    explicit ReportCommand(std::shared_ptr<LogRepository> repository)
            : repository(std::move(repository)) {}

    void execute() override {
        std::string filename = "report.txt";
        if (!args.empty()) {
            filename = args;
        }

        std::ofstream out(filename);
        if (!out.is_open()) {
            std::cerr << "[ReportCommand] Failed to open file: " << filename << "\n";
            return;
        }

        int warnings = 0, errors = 0, securityErrors = 0;
        std::map<std::string, int> errorTypes;
        std::map<std::string, int> moduleErrors;
        std::map<std::string, int> subsystemErrors;
        std::map<int, int> hourErrorHistogram;
        std::set<std::string> uniqueErrorMessages;
        std::string mostRecentError;
        std::tm latestTimestamp = {};

        for (const auto& log : repository->logs) {
            if (log.level == LogLevel::WARN) warnings++;
            if (log.level == LogLevel::ERROR) {
                errors++;
                errorTypes[log.message]++;
                moduleErrors[log.module]++;
                uniqueErrorMessages.insert(log.message);

                auto subsystem = log.module.substr(0, log.module.find("::"));
                subsystemErrors[subsystem]++;

                std::tm ts = {};
                auto time_t_timestamp = std::chrono::system_clock::to_time_t(log.timestamp);
                ts = *std::localtime(&time_t_timestamp);
                hourErrorHistogram[ts.tm_hour]++;

                if (log.message.find("SECURITY") != std::string::npos ||
                    log.message.find("TLS") != std::string::npos ||
                    log.message.find("CERTIFICATE") != std::string::npos)
                {
                    securityErrors++;
                }

                if (std::mktime(&ts) > std::mktime(&latestTimestamp)) {
                    latestTimestamp = ts;
                    mostRecentError = log.message;
                }
            }
        }

        // === Report ===
        out << "===== Log Analytics Report =====\n";
        out << "Warnings: " << warnings << "\n";
        out << "Errors: " << errors << "\n";
        out << "Unique error types: " << uniqueErrorMessages.size() << "\n";
        out << "Security-related errors: " << securityErrors << "\n\n";

        out << "Top error types:\n";
        for (const auto& [type, count] : errorTypes) {
            out << " - " << type << ": " << count << "\n";
        }

        std::string mostFailingModule;
        int maxErrors = 0;
        for (const auto& [mod, count] : moduleErrors) {
            if (count > maxErrors) {
                mostFailingModule = mod;
                maxErrors = count;
            }
        }
        out << "\nMost failing module: " << mostFailingModule << " (" << maxErrors << " errors)\n";

        out << "\nErrors by subsystem:\n";
        for (const auto& [subsystem, count] : subsystemErrors) {
            out << " - " << subsystem << ": " << count << "\n";
        }

        out << "\nError frequency by hour:\n";
        for (const auto& [hour, count] : hourErrorHistogram) {
            out << " - " << std::setw(2) << std::setfill('0') << hour << ":00 — " << count << "\n";
        }

        out << "\nMost recent error: " << mostRecentError << "\n";
        out << "Occurred at: "
            << std::put_time(&latestTimestamp, "%Y-%m-%d %H:%M:%S") << "\n";

        out << "================================\n";

        out.close();
        std::cout << "[ReportCommand] Report saved to '" << filename << "'\n";
    }

    void setArgs(const std::string& inputArgs) {
        args = inputArgs;
    }

private:
    std::shared_ptr<LogRepository> repository;
    std::string args;
};

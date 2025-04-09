#pragma once

#include "Command.hpp"
#include "Repository/LogRepository.hpp"
#include "Model/Log.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <utility>

class LoadFromFileCommand : public Command {
private:
    std::shared_ptr<LogRepository> repository;
    std::string args;

public:
    LoadFromFileCommand(std::shared_ptr<LogRepository>  repository, std::string  args)
            : repository(std::move(repository)), args(std::move(args)) {}

    void execute() override {
        repository->clear();
        if (args.empty()) {
            std::cout << "Please specify filename: loadFromFile <filename>\n";
            return;
        }

        std::ifstream file(args);
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << args << "\n";
            return;
        }

        size_t loadedCount = 0;
        size_t errorCount = 0;
        std::string line;

        while (std::getline(file, line)) {
            try {
                Log log = Log::fromString(line);
                repository->save(log);
                loadedCount++;
            } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line
                          << "\nReason: " << e.what() << "\n";
                errorCount++;
            }
        }

        std::cout << "Loading complete. Success: " << loadedCount
                  << ", Errors: " << errorCount
                  << ", Total: " << (loadedCount + errorCount) << "\n";
    }
};
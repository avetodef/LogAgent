#pragma once

#include "Command.hpp"
#include "Repository/LogRepository.hpp"
#include "Model/Log.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

class LoadFromFileCommand : public Command {
private:
    std::shared_ptr<LogRepository> repository;
    std::string args;
public:
    LoadFromFileCommand(const std::shared_ptr<LogRepository> &repository, const std::string &args) : repository(
            repository), args(args) {}

    void execute() override {
        if (args.empty()) {
            std::cout << "plz write filename: loadFromFile <filename>\n";
            return;
        }

        std::ifstream file(args);
        if (!file.is_open()) {
            std::cout << "couldn't open file: " << args << "\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Log log;
            char delimiter;

            int id;
            if (!(iss >> id >> delimiter) || delimiter != '|') {
                std::cout << "Error parsing ID in line: " << line << "\n";
                continue;
            }
            std::string timestamp;
            std::getline(iss, timestamp, '|');
            log.timestamp = timestamp;

            std::getline(iss, log.level, '|');

            std::getline(iss, log.module, '|');

            std::getline(iss, log.message);

            log.message.erase(0, log.message.find_first_not_of(" \t"));
            log.message.erase(log.message.find_last_not_of(" \t") + 1);

            repository->save(log);
        }
        std::cout << "loaded this many logs: " << repository->logs.size() << "\n";
    }
};

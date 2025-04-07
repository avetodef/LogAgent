#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "Model/Log.hpp"
#include "Repository/InMemoryRepository.hpp"
#include "Command/QueryCommand.hpp"

std::vector<Log> loadLogsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Log> logs;
    std::string line;

    while (std::getline(file, line)) {
        try {
            logs.push_back(Log::fromString(line));
        } catch (...) {
            std::cerr << "Parse error: " << line << std::endl;
        }
    }

    return logs;
}

int main() {
    std::cout << "Choose data source:\n1 - File\n2 - Database\n> ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    std::shared_ptr<LogRepository> repo;

    if (choice == 1) {
        std::string filename;
        std::cout << "Write filename: ";
        std::getline(std::cin, filename);

        auto logs = loadLogsFromFile(filename);
        repo = std::make_shared<InMemoryRepository>();
        repo->setLogs(logs);
    } else {
        std::cout << "Database is not done yet\n";
        return 1;
    }

    // Цикл команд
    std::string command;
    while (true) {
        std::cout << "\nInput command: ";
        std::getline(std::cin, command);

        if (command == "exit") break;

        if (command.rfind("query ", 0) == 0) {
            std::string queryArgs = command.substr(6);
            QueryCommand qc(queryArgs, repo);
            qc.execute();
        } else {
            std::cout << "Unknown command \n";
        }
    }

    return 0;
}

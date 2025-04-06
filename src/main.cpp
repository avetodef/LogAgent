#include <iostream>
#include <memory>
#include "FileRepository.hpp"
#include "Command.hpp"
#include "QueryCommand.hpp"
#include "AnalyticsCommand.hpp"

bool startsWith(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

int main() {
    std::string input;
    FileRepository repo;
    while (true) {
        std::cout << "Write a command " << std::endl;
        std::getline(std::cin, input);
        if (input == "exit") break;

        std::unique_ptr<Command> command;

        if (startsWith(input, "query")) {
            command = std::make_unique<QueryCommand>(input);
        } else if (startsWith(input, "analytic")) {
            command = std::make_unique<AnalyticCommand>(input);
        } else {
            std::cout << "Unknown command.\n";
            continue;
        }

        command->execute();
    }
    return 0;
}

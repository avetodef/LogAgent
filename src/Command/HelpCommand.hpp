#pragma once
#include "Command.hpp"
#include <vector>
#include <iostream>

class HelpCommand : public Command {
public:
    void execute() override {
        std::cout << "List of available commands:\n";
        std::cout << "  help                  - Show all available commands\n";
        std::cout << "  exit                  - Terminate the program\n";
        std::cout << "  query <filters>       - Search logs by criteria (time, module, method, level)\n";
        std::cout << "  analytics             - Show log statistics\n";
        std::cout << "  loadFromFile <file>   - Load logs from a text file\n";
        std::cout << "  report                - Save analytics results to a .txt file\n";
    }
};

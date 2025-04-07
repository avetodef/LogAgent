#pragma once
#include "Command.hpp"
#include <iostream>

class ExitCommand : public Command {
public:
    void execute() override {
        std::cout << "Goodbye...\n";
        exit(0);
    }
};

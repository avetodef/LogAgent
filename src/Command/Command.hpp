#pragma once
#include <string>

class Command {
public:
    Command() = default;
    explicit Command(const std::string& args) : args(args) {}
    virtual ~Command() = default;

    virtual void execute() = 0;

protected:
    std::string args;
};

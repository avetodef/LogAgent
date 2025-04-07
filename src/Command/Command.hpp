#pragma once
#include <string>
#include <utility>

class Command {
public:
    Command() = default;
    explicit Command(std::string  args) : args(std::move(args)) {}
    virtual ~Command() = default;

    virtual void execute() = 0;

protected:
    std::string args;
};

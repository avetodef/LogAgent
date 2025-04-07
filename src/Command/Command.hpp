#pragma once
#include "../Model/Log.hpp"
#include <string>
#include <vector>

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

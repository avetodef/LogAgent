#include "QueryCommand.hpp"
#include <iostream>
#include <sstream>
#include <memory>

QueryCommand::QueryCommand(const std::string& input, std::shared_ptr<LogRepository> repo)
        : input(input), repository(std::move(repo)) {}

void QueryCommand::execute() {
    // TODO
}

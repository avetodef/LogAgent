#pragma once

#include "Command.hpp"
#include "../Repository/LogRepository.hpp"
#include "../Criteria/Criteria.hpp"
#include <memory>
#include <string>

class QueryCommand : public Command {
private:
    std::string input;
    std::shared_ptr<LogRepository> repository;

public:
    QueryCommand(const std::string& input, std::shared_ptr<LogRepository> repo);

    void execute() override;
};

#pragma once

#include "Command.hpp"
#include "HelpCommand.hpp"
#include "QueryCommand.hpp"
#include "AnalyticsCommand.hpp"
#include "LoadFromFileCommand.hpp"
#include "ReportCommand.hpp"
#include "ExitCommand.hpp"
#include <memory>
#include <string>
#include <unordered_map>

class CommandFactory {
public:
    static std::unique_ptr<Command> create(    const std::string &commandName,
                                               const std::string &args,
                                               std::shared_ptr<LogRepository> repository) {
        if (commandName == "help") {
            return std::make_unique<HelpCommand>();
        } else if (commandName == "exit") {
            return std::make_unique<ExitCommand>();
        } else if (commandName == "query") {
            return std::make_unique<QueryCommand>(args, repository);
        } else if (commandName == "analytics") {
            return std::make_unique<AnalyticsCommand>(repository);
        } else if (commandName == "loadFromFile") {
            return std::make_unique<LoadFromFileCommand>(repository, args);
        } else if (commandName == "report") {
            return std::make_unique<ReportCommand>(repository);
        }

        return nullptr;
    }
};

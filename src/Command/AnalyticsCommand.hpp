#pragma once
#include "Command.hpp"
#include <iostream>

class AnalyticCommand : public Command {
public:
    explicit AnalyticCommand(const std::string& args) : Command(args) {}

    void execute() override {
        std::cout << "[AnalyticCommand] Executing analysis: " << args << std::endl;

        // Здесь будет парсинг типа аналитики и запуск агрегации
        // Пока просто выводим
    }
};

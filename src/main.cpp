#include <iostream>
#include <memory>
#include "Command/CommandFactory.hpp"
#include "Repository/InMemoryRepository.hpp"

int main() {
    std::shared_ptr<LogRepository> repository = std::make_shared<InMemoryRepository>();

    std::cout << "bello)\n";

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        std::istringstream iss(input);
        std::string commandName;
        iss >> commandName;

        std::string args;
        std::getline(iss, args);

        size_t firstChar = args.find_first_not_of(" \t");
        if (firstChar != std::string::npos) {
            args = args.substr(firstChar);
        } else {
            args.clear();
        }

        try {
            auto command = CommandFactory::create(commandName, args, repository);
            if (!command) {
                std::cout << "idk this command.\n";
                continue;
            }
            command->execute();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}

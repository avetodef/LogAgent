#pragma once
#include "Criteria.hpp"

class LogModuleCriteria : public Criteria {
private:
    std::string module;
public:
    LogModuleCriteria(const std::string& mod) : module(mod) {}

    bool isSatisfiedBy(const Log& log) const override {
        return log.module == module;
    }
};

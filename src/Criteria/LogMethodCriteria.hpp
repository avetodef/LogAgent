#pragma once
#include "Criteria.hpp"

class LogMethodCriteria : public Criteria {
private:
    std::string method;
public:
    LogMethodCriteria(const std::string& mtd) : method(mtd) {}

    bool isSatisfiedBy(const Log& log) const override {
        return log.sourceMethod == method;
    }
};

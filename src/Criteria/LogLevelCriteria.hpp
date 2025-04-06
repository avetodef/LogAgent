#pragma once
#include "Criteria.hpp"

class LogLevelCriteria : public Criteria {
private:
    LogLevel level;
public:
    LogLevelCriteria(LogLevel lvl) : level(lvl) {}

    bool isSatisfiedBy(const Log& log) const override {
        return log.level == level;
    }
};

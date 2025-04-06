#include "AggregationOperation.hpp"

#pragma once

class ErrorCountByModuleAggregation : public AggregationOperation {
public:
    std::string aggregate(const std::vector<Log>& logs) override {
        return "Error count by module calculated.";
    }
};
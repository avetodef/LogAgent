#include "AggregationOperation.hpp"

#pragma once

class MostFrequentErrorAggregation : public AggregationOperation {
public:
    std::string aggregate(const std::vector<Log>& logs) override {
        return "Most frequent error calculated.";
    }
};
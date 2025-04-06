#include <string>
#include <vector>
#include "src/Log.h"

#pragma once

class AggregationOperation {
public:
    virtual std::string aggregate(const std::vector<Log>& logs) = 0;
    virtual ~AggregationOperation() = default;
};

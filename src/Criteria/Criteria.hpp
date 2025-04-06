#include <string>
#include "Model/Log.hpp"

#pragma once

class Criteria {
public:
    virtual ~Criteria() = default;
    virtual bool isSatisfiedBy(const Log& log) const = 0;
};
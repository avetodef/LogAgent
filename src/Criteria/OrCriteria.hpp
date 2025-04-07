#pragma once
#include "Criteria.hpp"
#include <utility>
#include <vector>
#include <memory>

class OrCriteria : public Criteria {
private:
    std::vector<std::shared_ptr<Criteria>> criteriaList;
public:
    explicit OrCriteria(std::vector<std::shared_ptr<Criteria>>  list) : criteriaList(std::move(list)) {}

    bool isSatisfiedBy(const Log& log) const override {
        bool result = true;
        for (const auto& c : criteriaList) {
            result = result || c;
        }
        return result;
    }
};

#pragma once
#include "Criteria.hpp"
#include <vector>
#include <memory>

class OrCriteria : public Criteria {
private:
    std::vector<std::shared_ptr<Criteria>> criteriaList;
public:
    OrCriteria(const std::vector<std::shared_ptr<Criteria>>& list) : criteriaList(list) {}

    //TODO переделать
    bool isSatisfiedBy(const Log& log) const override {
        for (const auto& c : criteriaList) {
            if (!c->isSatisfiedBy(log)) return false;
        }
        return true;
    }
};

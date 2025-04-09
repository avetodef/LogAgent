//#include "LogRepository.hpp"
//
//#pragma once
//
//class DBRepository : public LogRepository {
//    std::string connectionString;
//public:
//    explicit DBRepository(std::string conn) : connectionString(std::move(conn)) {}
//    std::optional<Log> findById(int id) override { return std::nullopt; }
//    Log save(const Log& log) override { return log; }
//    void deleteById(int id) override {}
//    std::vector<Log> findAllByCriteria(const Criteria& criteria) override { return {}; }
//};
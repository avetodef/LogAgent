#pragma once
#include <string>

enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    UNKNOWN
};

inline std::string logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

inline LogLevel stringToLogLevel(std::string & s){
    if (s == "TRACE") return LogLevel::TRACE;
    if (s == "DEBUG") return LogLevel::DEBUG;
    if (s == "INFO") return LogLevel::INFO;
    if (s == "WARN") return LogLevel::WARN;
    if (s == "ERROR") return LogLevel::ERROR;
    return LogLevel::UNKNOWN;
}

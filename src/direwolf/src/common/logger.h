#pragma once

#define DEBUG_LOG(PRIORITY, MESSAGE) Logger::Write(PRIORITY, MESSAGE);

#include <string>

namespace dwf {

class Logger {
public:
    Logger() = delete;
    Logger(const Logger& logger) = delete;
    Logger& operator= (const Logger& logger) = delete;

    enum Severity {
        DEBUG,
        CONFIG,
        INFO,
        WARNING,
        ERR
    };

	static void Write(Severity severity, const std::string& message);
	static void Flush();
};

}

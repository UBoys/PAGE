#include "logger.h"

#include <fstream>
#include <iostream>

namespace {
    const std::string PRIORITY_NAMES[] = {
        "DEBUG",
        "CONFIG",
        "INFO",
        "WARNING",
        "ERROR"
    };

	std::ofstream s_fileStream;
	const std::string logFileName = "log.txt";
}

namespace dwf {

void Logger::Write(Severity severity, const std::string& message) {
	if (!s_fileStream.is_open()) {
		s_fileStream.open(logFileName.c_str());
	}

	std::string log = PRIORITY_NAMES[severity] + ": " + message + "\n";
	s_fileStream << log;
	std::cout << log;
}

void Logger::Destroy() {
	s_fileStream.close();
}

}

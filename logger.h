#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

class Logger {
	std::ofstream f;
	Logger(std::string);
	~Logger();
	void write(std::string);
	void operator<<(std::string);
};

#endif

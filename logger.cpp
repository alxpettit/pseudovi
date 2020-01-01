#include "logger.h"
#include <fstream>

Logger::Logger(std::string fname) {
	f.open(fname);
}

Logger::~Logger() {
	f.close();
}

void Logger::write(std::string str) {
	f << str;
}
void Logger::operator<<(std::string str) {
	f << str;
	return;
}

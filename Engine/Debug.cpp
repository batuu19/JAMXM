#include "Debug.h"

void Debug::clear()
{
	std::ofstream out("debug.txt", std::ios::trunc);
}

void Debug::writeMessage(std::string message, std::string filename)
{
	std::ofstream out(filename, std::ios::app);
	out.seekp(0, std::ios::end);

	auto now = time(0);
	tm* gmtm = gmtime(&now);
	char* dt = asctime(gmtm);

	out << dt <<message <<"\n";
}

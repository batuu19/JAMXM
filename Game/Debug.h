#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <time.h>

class Debug {

public:
	
	static void clear();
	static void writeMessage(std::string message, std::string filename = "debug.txt");
	static void writeError(std::string errorMessage, std::string filename = "debug.txt")
	{
		writeMessage("Error: " + errorMessage);
	}
	static void writeWarning(std::string warningMessage, std::string filename = "debug.txt")
	{
		writeMessage("Warning: " + warningMessage);
	}
	static void writeInfo(std::string infoMessage, std::string filename = "debug.txt")
	{
		writeMessage("Info: " + infoMessage);
	}

};
#pragma once
#include <string>
#include <sstream>

inline std::string getMapImageFilename(int i) 
{
	std::stringstream ss;
	ss << "sprites\\maps\\w" << i << ".bmp";
	return ss.str();
}
inline std::string getAIFilename(int i)
{
	std::stringstream ss;
	ss << "logic\\w" << i << ".ai";
	return ss.str();
}
inline std::string getMapHitboxFilename(int i)
{
	std::stringstream ss;
	ss << "logic\\r" << i << ".map";
	return ss.str();
}
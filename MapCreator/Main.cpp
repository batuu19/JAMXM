#pragma once
#include <iostream>
#include "Map.h"

int main()
{
	Map map = Map();
	map.generateFile("testMap.txt", "out.jpg");
}
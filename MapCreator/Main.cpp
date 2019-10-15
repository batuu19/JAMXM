#include "Main.h"
#include "Map.h"

int main()
{
	Map map = Map();
	map.generateFile("testMap.txt", "ttt");
	system("pause");
}
#include "Main.h"
#include "Map.h"

int main()
{
	Map map = Map();
	map.generateFile("testNumbers.txt", "ttt");
	system("pause");
}
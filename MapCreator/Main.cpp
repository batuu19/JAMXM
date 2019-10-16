#include "Main.h"
#include "Map.h"

int main()
{
	Map map = Map(100,100,5,5);
	map.generateFile("testMap.txt", "out.jpg");
}
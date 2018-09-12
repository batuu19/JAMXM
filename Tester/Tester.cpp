// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream in("r0.map", std::ios::binary);
	if (!in.good())return -1;
	char data;
	while (in.get(data))
	{
		for (int i = 6; i >= 0; i -= 2)
		{
			if ((data >> i) & 3)
			{
				std::cout << (int)data << " "<<in.tellg()<<"\n";
				std::cin.ignore();
			}
		}
	}

    return 0;
}


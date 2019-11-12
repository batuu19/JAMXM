// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

std::vector<int>& getP()
{
	std::vector<int> data = { 5,1,3,6,7,8,1 };

	return data;
}

int main()
{
	std::vector<int> vec1 = { 1,2,3,4,5,6,7,8,9 };
	std::vector<int> vec2 = { 3,4,8,9 };

	auto data = getP();
	std::cout << data[3] << "\n";
	std::cin.ignore();
    return 0;
}


// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

int main()
{
	std::vector<int> vec1 = { 1,2,3,4,5,6,7,8,9 };
	std::vector<int> vec2 = { 3,4,8,9 };

	auto vec3 = std::transform(vec1.begin(), vec1.end(), vec1.begin(), [](int i) {return i + 111; });
	bool data = std::includes(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

	std::cout << data << "\n";
	std::cin.ignore();
    return 0;
}


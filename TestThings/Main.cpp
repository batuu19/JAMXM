#include <memory>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
	std::vector<int> vec(10);
	std::iota(vec.begin(), vec.end(), 0);

	auto it = std::remove_if(vec.begin(), vec.end(), [](int a) {return a % 3 == 0; });

	std::vector<int> newVec(vec.begin(), it);

}
#include<iostream>
#include<string>
#include"chapter-01/Test01.h"
#include"chapter-02/Test02.h"


int main(int argc, char *argv[])
{
	std::vector<char> tmp;
	for (uint64_t i = 0; i < UINT32_MAX; ++i)
	{
		tmp.push_back(0);
	}

	uint64_t result = std::accumulate(tmp.begin(), tmp.end(), 0ull);

	//unsigned long long result = parallel_accumulate<std::vector<int>::iterator, unsigned long long>(tmp.begin(), tmp.end(), 0ULL);

	std::cout << result << std::endl;

	system("pause");
	return 0;
}
#include <iostream>
#include <string>
#include "chapter-practice/ThreadPool.h"

int main(int argc, char *argv[])
{
	auto f = []()
	{
		std::cout << "test: thread;" << "\n";
		std::string result = "result";
		return result;
	};

	auto ret = Pool().addOnce(f);

	auto result = ret.get();

	std::cout << result << std::endl;

	system("pause");
	return 0;
}
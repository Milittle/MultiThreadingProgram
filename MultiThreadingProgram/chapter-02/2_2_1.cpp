#include"Test02.h"


void process_unique_ptr(std::unique_ptr<std::string> test)
{
	std::cout << *test << std::endl;
}

void Test02::test_2_2_1()
{
	std::unique_ptr<std::string> p(new std::string("hello"));
	std::thread t(process_unique_ptr, std::move(p));
	if (t.joinable())
		t.join();
}
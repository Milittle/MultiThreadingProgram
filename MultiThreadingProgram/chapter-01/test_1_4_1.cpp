#include"Test01.h"

void cout_hello()
{
	std::cout << "hello multiThread\n";
}

void Test01::test_1_4_1()
{
	//每个线程必须有一个初始化的方法
	std::thread t(cout_hello);
	//主线程通过等待t新建的线程
	t.detach();
	//t.join();
}
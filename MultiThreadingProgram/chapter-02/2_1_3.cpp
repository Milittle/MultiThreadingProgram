#include"Test02.h"


struct MyStruct;

void Test02::test_2_1_3()
{
	int state = 0;
	MyStruct my(state);
	std::thread t(my);
	try 
	{
		//do_some_thing_in_current_thread not thread (t);
	}
	catch (...)
	{
		t.join();
		throw;
	}
	if (t.joinable()) t.join();
}

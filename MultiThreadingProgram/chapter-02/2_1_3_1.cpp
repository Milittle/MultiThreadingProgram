#include"Test02.h"
#include<chrono>
#include<ctime>

void Test02::test_2_1_3_1()
{
	int i = 0;
	MyStruct my(i);

	std::thread t(my);
	ThreadGuard tg{t};

	//do_some_thing();
}//当执行到这里时,局部对象会被逆序销毁,则线程t就会被调用join方法和主线程联系在一起
//就算do_some_thing()会出现异常,这个销毁也会正常发生.
//这样就确保了线程对象不管咋样 都会执行等待或者分离方法.



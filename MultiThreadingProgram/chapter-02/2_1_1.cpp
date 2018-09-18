#include"Test02.h"

//以下代码需要注意的是不能传给线程对象一个临时变量:
/*
* 如果你传给线程构造函数一个临时变量:
	std::thread my_thread(BackroundTask());
	这个语法会将my_thread变成一个函数对象
* 为了避免这种情况发生:
	std::thread my_thread((BackroundTask())); //以表达式的形式传入
	std::thread my_thread{BackroundTask()}; //以列表初始化的方式传入
	也可以通过lambda表达式避免以上问题:
	std::thread my_thread([]()->{do_some_thing(); do_some_thing_else();});
*/

void Test02::test_2_1_1()
{
	BackgroundTask task;
	//会将以上函数对象复制到新线程的存储空间中,函数对象的执行和调用都在新线程的内存空间里面进行.
	//构建线程并启动线程
	std::thread t(task);
	t.join();
}
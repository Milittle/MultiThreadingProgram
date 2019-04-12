#include"Test03.h"


some_data *unprotected;

void malicious_function(some_data &protected_data)
{
	unprotected = &protected_data;
}

//前提是需要保护x这个共享数据的一致性
data_wrapper x;
void Test03::test_3_2()
{
	//如果test_3_2是一个多线程访问的程序,那么就要保证这一点
	x.process_data<>(malicious_function);

	//malicious_function将x对象中的some_data对象的引用传递到了unprotected对象中
	//致使在外部离开了func以后,可以对x的数据进行破坏,这一点是不允许的
	//所以以后需要多加注意,共享数据的传输和保护(不要让应用或者指针的方式传出lock保护作用域)
	unprotected->do_some_thing();
}
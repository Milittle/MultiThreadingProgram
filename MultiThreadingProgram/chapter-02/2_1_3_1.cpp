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
}//��ִ�е�����ʱ,�ֲ�����ᱻ��������,���߳�t�ͻᱻ����join���������߳���ϵ��һ��
//����do_some_thing()������쳣,�������Ҳ����������.
//������ȷ�����̶߳��󲻹�զ�� ����ִ�еȴ����߷��뷽��.



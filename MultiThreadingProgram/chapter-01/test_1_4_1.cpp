#include"Test01.h"

void cout_hello()
{
	std::cout << "hello multiThread\n";
}

void Test01::test_1_4_1()
{
	//ÿ���̱߳�����һ����ʼ���ķ���
	std::thread t(cout_hello);
	//���߳�ͨ���ȴ�t�½����߳�
	t.detach();
	//t.join();
}
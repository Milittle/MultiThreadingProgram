#include"Test02.h"

//���´�����Ҫע����ǲ��ܴ����̶߳���һ����ʱ����:
/*
* ����㴫���̹߳��캯��һ����ʱ����:
	std::thread my_thread(BackroundTask());
	����﷨�Ὣmy_thread���һ����������
* Ϊ�˱��������������:
	std::thread my_thread((BackroundTask())); //�Ա��ʽ����ʽ����
	std::thread my_thread{BackroundTask()}; //���б��ʼ���ķ�ʽ����
	Ҳ����ͨ��lambda���ʽ������������:
	std::thread my_thread([]()->{do_some_thing(); do_some_thing_else();});
*/

void Test02::test_2_1_1()
{
	BackgroundTask task;
	//�Ὣ���Ϻ��������Ƶ����̵߳Ĵ洢�ռ���,���������ִ�к͵��ö������̵߳��ڴ�ռ��������.
	//�����̲߳������߳�
	std::thread t(task);
	t.join();
}
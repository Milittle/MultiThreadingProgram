#include"Test03.h"


some_data *unprotected;

void malicious_function(some_data &protected_data)
{
	unprotected = &protected_data;
}

//ǰ������Ҫ����x����������ݵ�һ����
data_wrapper x;
void Test03::test_3_2()
{
	//���test_3_2��һ�����̷߳��ʵĳ���,��ô��Ҫ��֤��һ��
	x.process_data<>(malicious_function);

	//malicious_function��x�����е�some_data��������ô��ݵ���unprotected������
	//��ʹ���ⲿ�뿪��func�Ժ�,���Զ�x�����ݽ����ƻ�,��һ���ǲ������
	//�����Ժ���Ҫ���ע��,�������ݵĴ���ͱ���(��Ҫ��Ӧ�û���ָ��ķ�ʽ����lock����������)
	unprotected->do_some_thing();
}
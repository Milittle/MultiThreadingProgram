#include"Test02.h"


bool done_editing()
{
	return false;
}

//ʹ�ö���̴߳��������ݷ�����ĵ�
//ע��detach�Ժ����߳̾������߳�û��ֱ�ӹ�ϵ,���߳�ִ���깤���Ժ�
//���߳�����ȴ����߳�,���̻߳��Լ��Է���ķ�ʽ�ͷ���Դ
void Test02::test_2_1_4(const std::string &filename)
{
	//open_document_and_display_gui(filename)
	while (!done_editing())
	{
		//user_command cmd = get_user_input();
		/*
		if(cmd.type == open_new_document)
		{
			const std::string new_name = get_filename_from_user();
			std::thread t(edit_document, new_name);
			t.detach();
		}
		else
		{
			process_user_cmd(cmd);
		}
		*/
	}
}

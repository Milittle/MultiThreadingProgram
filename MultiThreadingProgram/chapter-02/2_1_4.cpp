#include"Test02.h"


bool done_editing()
{
	return false;
}

//使用多个线程处理多个数据分离的文档
//注意detach以后新线程就与主线程没有直接关系,主线程执行完工作以后
//主线程无须等待新线程,新线程会自己以分离的方式释放资源
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

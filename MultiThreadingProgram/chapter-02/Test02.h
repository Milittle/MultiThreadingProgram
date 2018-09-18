#pragma once
#include<numeric>
#include<algorithm>
#include<string>
#include<iostream>
#include<thread>
#include<vector>

class Test02
{
public:
	Test02() = default;
	~Test02();


	void test_2_1_1();
	void test_2_1_2();
	void test_2_1_3();
	void test_2_1_3_1();
	void test_2_1_4(const std::string & filename);
	void test_2_2_1();
};


class BackgroundTask 
{
public:
	void operator()()
	{
		do_some_thing();
		do_some_thing_else();
	}

	void do_some_thing() { std::cout << "do some thing\n"; }
	void do_some_thing_else() { std::cout << "do something\n"; }
public:
	
};


struct MyStruct
{
	int &i_;
	MyStruct(int &i) : i_(i) {}
	void operator() ()
	{
		for (int j = 0; j < 1000000; ++j)
		{
			do_some_thing(i_);
		}
	}

	static void hello() { std::cout << "hello world" << std::endl; }

	void do_some_thing(int &i) { std::cout << "The value i is: " << i << std::endl; }
};


//ʹ�ô���,���Ա�֤��ʹ�þֲ�����ʱ��,���̶߳����װ���������,
//��֤������̶߳��������ٵ�֮ǰ����join����
//�ھֲ�������������쳣Ҳ�ᱣ֤�̶߳������������
class ThreadGuard {
public:
	explicit ThreadGuard (std::thread &t):t_(t){}
	ThreadGuard(const ThreadGuard &) = delete;
	ThreadGuard & operator = (const ThreadGuard &) = delete;

	~ThreadGuard()
	{
		if (t_.joinable())
			t_.join();
	}

private:
	std::thread& t_;
};



//����ɵ���ģ�������ʵ����accumulate�ķ�װ
template <typename Iterator, typename T>
struct accumulate_block {
	void operator ()(Iterator first, Iterator last, T &result)
	{
		result = std::accumulate(first, last, result);
	}
};


//���ģ�庯��ʵ���˲�����͵ķ�װ
template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
	const unsigned long length = std::distance(first, last);
	if (!length)
		return init;

	const unsigned long min_per_threads = 25;
	const unsigned long max_threads = (length + min_per_threads - 1) / min_per_threads;
	const unsigned long hardware_threads = std::thread::hardware_concurrency();

	const unsigned long num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	const unsigned long block_size = length / num_threads;

	std::vector<T> results(num_threads);
	std::vector<std::thread> threads(num_threads - 1);

	Iterator block_start = first;

	for (unsigned long i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		threads[i] = std::thread(
			accumulate_block<Iterator, T>(), //���ǹ���һ������
			block_start, 
			block_end, 
			std::ref(results[i])
		);

		block_start = block_end;
	}

	accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

	return std::accumulate(results.begin(), results.end(), init);
}
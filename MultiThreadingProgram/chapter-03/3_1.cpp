#include"Test03.h"

//其实一般是要封装在类里面的
std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
	//lock_guard使用RAII机制来保证mutex的lock和unlock
	std::lock_guard<std::mutex> guard{ some_mutex };
	some_list.push_back(new_value);
}

bool list_containes(int value_to_find)
{
	//lock_guard使用RAII机制来保证mutex的lock和unlock
	std::lock_guard<std::mutex> guard{ some_mutex };
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

void Test03::test_3_1(const std::vector<int> &add_lists)
{
	unsigned long list_size = add_lists.size();
	unsigned num_threads = std::thread::hardware_concurrency();
	unsigned long block_size = list_size / num_threads;

	std::vector<std::thread> threads(num_threads);

	auto block_start = add_lists.begin();
	auto block_end = block_start + block_size;

	for (unsigned i = 0; i < num_threads - 1; ++i)
	{
		for (auto it = block_start; it != block_end; ++it)
		{
			threads[i] = std::thread(
				add_to_list,
				*it
			);
		}
		block_start = block_end;
		block_end = block_end + block_size;
	}

	for (auto it = block_start; it != add_lists.end(); ++it)
	{
		threads[num_threads - 1] = std::thread(
			add_to_list,
			*it
		);
	}
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}
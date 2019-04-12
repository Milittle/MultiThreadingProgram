#pragma once
#include<iostream>
#include<algorithm>
#include<list>
#include<mutex>
#include<thread>
#include<vector>
#include<string>
class Test03
{
public:
	Test03() = default;
	~Test03();

	void test_3_1(const std::vector<int> &add_lists);
	void test_3_2();
};



//3-2
class some_data
{
public:

	some_data() = default;
	~some_data() {};

	void do_some_thing();
private:
	int a;
	std::string s;

};

class data_wrapper
{
public:
	data_wrapper() = default;
	~data_wrapper() {};

	template<typename Function>
	void process_data(Function func)
	{
		std::lock_guard<std::mutex> lock{mutex};
		func(data);
	}
private:
	some_data data;
	std::mutex mutex;
};



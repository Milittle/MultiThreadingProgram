#pragma once
#include<iostream>
#include<list>
#include<deque>
#include<vector>
#include <stack>

template<typename T, typename Container = std::deque<T> >
class stack_3_3
{
public:
	explicit stack_3_3(const Container &) {};
	explicit stack_3_3(Container && = Container()) {};
	template<class Alloc> explicit stack_3_3(const Alloc &) {};
	template<class Alloc> stack_3_3(const Container &, const Alloc &) {};
	template<class Alloc> stack_3_3(Container &&, const Alloc &) {};
	template<class Alloc> stack_3_3(stack_3_3 &&, const Alloc &) {};

	bool empty() const {};
	std::size_t size() const {};
	T & top() {};
	const T & top() const {};
	void push(const T &) {};
	void push(T &&) {};
	void pop() {};
	void swap(std::stack<T> &&) {};
};


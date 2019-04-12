#include "ThreadPool.h"

using tp::ThreadPool;

ThreadPool & ThreadPool::getInstance()
{
	static ThreadPool pool(8);
	return pool;
}

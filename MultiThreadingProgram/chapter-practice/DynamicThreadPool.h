#pragma once
#include <queue>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class DynamicThreadPool
{
public:
	DynamicThreadPool(int reserve_threads);
	~DynamicThreadPool();

	void Add(const std::function<void()> &callback);

private:
	class DynamicThread {
	public:
		DynamicThread(DynamicThreadPool * pool);
		~DynamicThread();
	private:
		DynamicThreadPool *pool_;
		std::unique_ptr<std::thread> thread_;
		void ThreadFunc();
	};

	void ThreadFunc();
	void ReapThreads(std::list<DynamicThread*> *tlist);

	std::mutex mu_;
	std::condition_variable cv_;
	std::condition_variable shutdown_cv_;

	bool shutdown_;
	std::queue<std::function<void()>> callbacks_;
	int reserve_threads_;
	int nthreads_;
	int threads_waiting_;
	std::list<DynamicThread*> dead_threads_;
};


//DynamicThread
DynamicThreadPool::DynamicThread::DynamicThread(DynamicThreadPool *pool)
	:pool_(pool),
	thread_(new std::thread(&DynamicThreadPool::DynamicThread::ThreadFunc, this))
{
}

DynamicThreadPool::DynamicThread::~DynamicThread()
{
	if (thread_->joinable())
	{
		thread_->join();
		thread_.reset();
	}
}

void DynamicThreadPool::DynamicThread::ThreadFunc()
{
	pool_->ThreadFunc();
	//ִ�������˳��Ժ�ͽ����̷߳���dead_threads_�У��ȴ�����
	std::unique_lock<std::mutex>lock(pool_->mu_);
	pool_->nthreads_--;
	pool_->dead_threads_.emplace_back(this);

	if ((pool_->shutdown_) && (pool_->nthreads_ == 0))
	{
		pool_->shutdown_cv_.notify_one();
	}
}
//DynamicThread end

DynamicThreadPool::DynamicThreadPool(int reserve_threads)
	:shutdown_(false),
	reserve_threads_(reserve_threads),
	nthreads_(0),
	threads_waiting_(0)
{
	for (int i = 0; i < reserve_threads_; ++i)
	{
		std::lock_guard<std::mutex> lock(mu_);
		nthreads_++;
		new DynamicThread(this);
	}
}

DynamicThreadPool::~DynamicThreadPool()
{
	std::unique_lock<std::mutex> lock(mu_);
	shutdown_ = true;
	cv_.notify_all();

	while (nthreads_ != 0)
	{
		shutdown_cv_.wait(lock);
	}

	ReapThreads(&dead_threads_);
}

void DynamicThreadPool::ReapThreads(std::list<DynamicThread*> *tlist)
{
	for (auto t = tlist->begin(); t != tlist->end(); t = tlist->erase(t))
	{
		delete *t;
	}
}

void DynamicThreadPool::Add(const std::function<void()> &callback)
{
	std::lock_guard<std::mutex> lock(mu_);
	callbacks_.push(callback);
	if (threads_waiting_ == 0)
	{
		nthreads_++;
		new DynamicThread(this);
	}
	else
	{
		cv_.notify_one();
	}

	if (!dead_threads_.empty())
	{
		ReapThreads(&dead_threads_);
	}
}

void DynamicThreadPool::ThreadFunc()
{
	for (;;)
	{
		std::unique_lock<std::mutex> lock(mu_);
		// ����������Ϊ�գ��Ǿ����Լ�����
		if (!shutdown_ && callbacks_.empty())
		{
			// ����Ѿ����㹻��Ŀ����̣߳���ô���˳��Լ�
			if (threads_waiting_ >= reserve_threads_)
			{
				break;
			}
			threads_waiting_++;
			cv_.wait(lock);       // ��������
			threads_waiting_--;
		}

		// �ж� shutdown ֮ǰ��Ҫ��֤�������񶼱�ִ����
		if (!callbacks_.empty())
		{
			auto cb = callbacks_.front();
			callbacks_.pop();
			lock.unlock();
			cb();
		}
		else if (shutdown_)
		{
			break;
		}
	}
}


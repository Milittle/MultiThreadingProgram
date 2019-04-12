#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <vector>
#include <utility>

namespace tp {

	class ThreadGuard
	{
	public:
		ThreadGuard(std::vector<std::thread> & threads) :
			threads_(threads){}

		ThreadGuard(ThreadGuard&&) = delete;
		ThreadGuard & operator=(ThreadGuard&&) = delete;

		ThreadGuard(const ThreadGuard&) = delete;
		ThreadGuard& operator=(const ThreadGuard&) = delete;

		~ThreadGuard()
		{
			for (size_t i = 0; i < threads_.size(); ++i)
			{
				if (threads_[i].joinable())
				{
					threads_[i].join();
				}
			}
		}

	private:
		std::vector<std::thread> & threads_;
	};

	class ThreadPool
	{
	public:
		using task_type = std::function<void()>;

	public:
		ThreadPool(ThreadPool&&) = delete;
		ThreadPool& operator=(ThreadPool&&) = delete;
		ThreadPool(const ThreadPool&) = delete;
		ThreadPool& operator=(const ThreadPool&) = delete;

		static ThreadPool & getInstance();

		~ThreadPool() {}

		template <typename Function, typename... Args>
		auto addOnce(Function&& f, Args&&...args)->std::future<typename std::result_of<Function(Args...)>::type>;

	private:
		explicit ThreadPool(int n);
		void doo();

		std::atomic<bool> stop_;
		std::mutex mutex_;
		std::condition_variable cond_;

		std::queue<task_type> tasks_;
		std::vector<std::thread> threads_;
		ThreadGuard threadGuard_;
	};

	inline ThreadPool::ThreadPool(int n) :
		stop_(false),
		threadGuard_(threads_)
	{
		int nthreads = n;
		if (nthreads <= 0)
		{
			nthreads = std::thread::hardware_concurrency();
			nthreads = (nthreads == 0 ? 2 : nthreads);
		}

		for (size_t i = 0; i < nthreads; ++i)
		{
			threads_.emplace_back(std::thread{ &ThreadPool::doo, this });
		}
	}

	inline void ThreadPool::doo() {

		while (!stop_.load(std::memory_order_acquire))
		{
			task_type task;

			{
				std::unique_lock<std::mutex> lock{ mutex_ };
				cond_.wait(lock, [this]() {return stop_.load(std::memory_order_acquire) || !this->tasks_.empty(); });

				if (stop_.load(std::memory_order_acquire))
				{
					return;
				}

				task = std::move(this->tasks_.front());
				tasks_.pop();
			}

			task();
		}
	}

	template <typename Function, typename... Args>
	auto ThreadPool::addOnce(Function&& fn, Args&&... args)->std::future<typename std::result_of<Function(Args...)>::type>
	{
		using return_type = typename std::result_of<Function(Args...)>::type;
		using task = std::packaged_task<return_type()>;

		auto t = std::make_shared<task>(std::bind(std::forward<Function>(fn), std::forward<Args>(args)...));

		auto ret = t->get_future();

		{
			std::lock_guard<std::mutex>lg{ mutex_ };
			if (stop_.load(std::memory_order_acquire))
			{
				throw std::runtime_error("thread pool stopped!!!");
			}
			tasks_.emplace([t]() {(*t) (); });
		}

		cond_.notify_all();
		return ret;
	}
} //tp ended

static auto Pool = std::function<tp::ThreadPool&()>(tp::ThreadPool::getInstance);
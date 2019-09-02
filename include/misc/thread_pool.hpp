#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

template <class F>
struct ThreadPool
{
	using function_t = std::function<F>;

	ThreadPool();
	~ThreadPool();

	void add_job(function_t func);

private:
	std::vector<std::thread> threads;
	std::mutex queue_mutex;
	std::condition_variable cv;
	std::queue<function_t> queue;
	bool running = true;
};

#endif
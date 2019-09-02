#include "misc/thread_pool.hpp"

// Reference code from here https://gist.github.com/LPeter1997/38de22f81be78eff49ad00ef05db9252

template <class F>
ThreadPool<F>::ThreadPool()
{
	auto nthreads = std::thread::hardware_concurrency();
	for (std::size_t i = 0; i < nthreads; ++i)
	{
		threads.emplace_back([this] {
			for (;;)
			{
				function_t job;
				{
					auto lck = std::unique_lock<std::mutex>(queue_mutex);

					cv.wait(lck, [this] { return !running || !queue.empty(); });

					if (!running && queue.empty())
					{
						return;
					}

					job = std::move(queue.front());
					queue.pop();
				}
				job();
			}
		});
	}
};

template <class F>
ThreadPool<F>::~ThreadPool()
{
	{
		auto lck = std::unique_lock<std::mutex>(queue_mutex);
		running = false;
	}
	cv.notify_all();
	for (auto &t : threads)
	{
		t.join();
	}
};

template <class F>
void ThreadPool<F>::add_job(function_t func)
{
	{
		auto lck = std::unique_lock<std::mutex>(queue_mutex);
		queue.push(func);
	}
	cv.notify_one();
};
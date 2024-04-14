#include<iostream>
#include<thread>
#include<mutex>
#include<string>

#include<condition_variable>
#include<queue>
#include<vector>
#include<functional>

#define Println(x) std::cout << x << std::endl
#define Print(x) std::cout << x << " "
#define Println(x, y) std::cout << x << y << std::endl

class ThreadPool
{
public:
	ThreadPool(int numThreads) : isStop(false)
	{
		for (int i = 0; i < numThreads; ++i) {
			threads.emplace_back([this] {
				while (1) {
					std::unique_lock<std::mutex> lock(mtx);
					condition.wait(lock, [this] {
						return !tasks.empty() || isStop;
						});

					if (isStop && tasks.empty()) {
						return;
					}

					std::function<void()> task(std::move(tasks.front()));
					tasks.pop();
					lock.unlock();
					task();
				}
				});
		}
	}

	~ThreadPool()
	{
		//{

		std::unique_lock<std::mutex> lock(mtx);
		isStop = true;
		//}

		condition.notify_all();
		for (auto& t : threads) {
			t.join();
		}
	}

	// 函数模板中，使用右值引用是万能引用（既能传入左值引用，也能传入右值引用）
	template<class F, class... Args>
	void enqueue(F&& f, Args&&... args)
	{
		// 因为上面的 f 和 args 既可能是左值引用，也可能是右值引用，需要在下面表现出来：使用完美转发
		std::function<void()> task =
			std::bind(std::forward<F>(f), std::forward<Args>(args)...);

		{
			std::unique_lock<std::mutex> lock(mtx);
			// std::move, 如果 task 是一个左值，那么会将它转化为一个右值传进去
			tasks.emplace(std::move(task));
		}
		condition.notify_one();
	}
private:
	std::vector<std::thread> threads;
	std::queue <std::function<void()>> tasks;

	std::mutex mtx;
	std::condition_variable condition;

	bool isStop;
};

//int main()
//{
//	ThreadPool pool(4);
//
//	for (int i = 0; i < 10; ++i) {
//		pool.enqueue([i] {
//			std::cout << "task : " << i << " is running" << std::endl;
//			std::this_thread::sleep_for(std::chrono::seconds(1));
//			std::cout << "task : " << i << " is done" << std::endl;
//
//			});
//	}
//
//	return 0;
//}

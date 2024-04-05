#include<iostream>
#include<thread>
#include<mutex>
#include<string>

#include<condition_variable>
#include<queue>


#define Println(x) std::cout << x << std::endl
#define Print(x) std::cout << x << " "
#define Println(x, y) std::cout << x << y << std::endl

std::queue<int> goods_queue;
std::condition_variable goods_cv;

std::mutex mtx;

void Producer()
{
	for (int i = 0; i < 10; ++i) {
		// 这个大括号 {} 限定了 unique_lock 的作用域
		// 去掉大括号 {} 后，一旦上锁，就需要整个 for 循环结束才解锁
		{
			std::unique_lock<std::mutex> lock(mtx);
			goods_queue.push(i);
			// 通知消费者来取任务
			goods_cv.notify_one();
			//Println("Producer : ", i);
			std::cout << "Producer : " << i << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::microseconds(100));

	}
}

void Consumer()
{
	while (1) {
		std::unique_lock<std::mutex> lock(mtx);
		// 如果队列为空，就要等待
		goods_cv.wait(lock, []() {
			return !goods_queue.empty();
			});
		// wait 的时候会释放锁，这时候 Producer 就能干活了

		int value = goods_queue.front();
		goods_queue.pop();

		std::cout << "Consumer : " << value << std::endl;
		//Println("Consumer : ", value);
	}
}

int main()
{
	std::thread t1(Producer);
	std::thread t2(Consumer);

	t1.join();
	t2.join();
	return 0;
}
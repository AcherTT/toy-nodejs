#include <iostream>
#include <thread.hpp>
#include <thread/thread_pool.hpp>

void task(int i)
{
    std::cout << "Thread " << boost::this_thread::get_id() << " processing task " << i << std::endl;
}

int main()
{
    boost::asio::thread_pool tp(2); // 创建线程池，初始大小为2

    // 提交10个任务
    for (int i = 0; i < 10; ++i)
    {
        tp.submit(boost::bind(task, i));
    }

    tp.wait(); // 等待所有任务完成

    return 0;
}

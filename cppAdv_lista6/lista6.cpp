#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <algorithm>
#include <functional>
#include <condition_variable>
#include <queue>

//zadanie 1
void sort_half(std::vector<int> w)
{
    std::cout << "Thread 1 started" << std::endl;
    std::sort(w.begin(), w.begin() + w.size() / 2);
    for (auto i : w)
    {
        std::cout << i << std::endl;
    }
    std::cout << "Thread 1 done" << std::endl;
}
void sort_rest(std::vector<int> w)
{
    std::cout << "Thread 2 started" << std::endl;
    std::sort(w.begin() + w.size() / 2, w.end());
    for (auto i : w)
    {
        std::cout << i << std::endl;
    }
    std::cout << "Thread 2 done" << std::endl;
}
//zadanie 2
class thread_pool {
public:
    using Task = std::function<double()>;
    thread_pool(std::size_t ThreadNum) {
        start(ThreadNum);
    }
    double average() {
        std::unique_lock<std::mutex> lock{ resultMutex };
        if (results.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        for (const auto& result : results) {
            sum += result;
        }
        return sum / results.size();
    }
    void add_task(Task task)
    {
        {
            std::unique_lock<std::mutex> lock{ mEventMutex };
            mTasks.emplace(std::move(task));
        }

        mEventVar.notify_one();
    }

    ~thread_pool() {
        stop();
    };
private:
    std::vector<std::thread> threads;
    std::condition_variable mEventVar;
    std::mutex mEventMutex;
    bool mStopping = false;
    std::queue<Task> mTasks;

    std::vector<double> results;
    std::mutex resultMutex;

    void start(std::size_t ThreadNum) {
        for (size_t i = 0u; i < ThreadNum; i++)
        {
            threads.emplace_back([=] {
                while (true)
                {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock{ mEventMutex };

                        mEventVar.wait(lock, [=] { return mStopping || !mTasks.empty(); });

                        if (mStopping && mTasks.empty())
                            break;

                        task = std::move(mTasks.front());
                        mTasks.pop();
                    }
                    double result = task();
                    {
                        std::unique_lock<std::mutex> lock{ resultMutex };
                        results.push_back(result);
                    }
                }
                });
        }
    };
    void stop() {
        {
            std::unique_lock<std::mutex> lock(mEventMutex);
            mStopping = true;
        }

        mEventVar.notify_all();

        for (auto& thread : threads)
        {
            thread.join();
        }
    }
};
int main()
{
    srand(time(NULL));
    std::vector<int> v;
    for (int i = 0; i < 1000; i++)
    {
        v.push_back(rand() % 100 + 1);
    }
    std::thread t1(sort_half, std::ref(v));
    t1.join();
    std::thread t2(sort_rest, std::ref(v));
    t2.join();
    {
        thread_pool pool{ 4 };

        pool.add_task([] {
            return 42.0;
            });

        pool.add_task([] {
            return 56.0;
            });

        pool.add_task([] {
            return 36.0;
            });

        pool.add_task([] {
            return 12.0;
            });

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << pool.average() << std::endl;
    }
    return 0;
}

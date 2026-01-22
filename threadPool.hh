#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

class ThreadPool {
public:
  // 构造函数：启动固定数量的工作线程
  explicit ThreadPool(size_t threads) : stop_(false) {
    for (size_t i = 0; i < threads; ++i) {
      workers_.emplace_back([this] {
        for (;;) {
          std::function<void()> task;

          {
            // 获取锁
            std::unique_lock<std::mutex> lock(this->queue_mutex_);

            // 等待条件：线程池停止 或 任务队列不为空
            this->condition_.wait(
                lock, [this] { return this->stop_ || !this->tasks_.empty(); });

            // 如果线程池停止且任务队列为空，则线程退出
            if (this->stop_ && this->tasks_.empty())
              return;

            // 取出任务
            task = std::move(this->tasks_.front());
            this->tasks_.pop();
          }

          // 执行任务
          task();
        }
      });
    }
  }

  // 析构函数：停止所有线程
  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(queue_mutex_);
      stop_ = true;
    }

    // 唤醒所有等待的线程，让它们检查 stop_ 标志并退出
    condition_.notify_all();

    // 等待所有线程结束
    for (std::thread &worker : workers_) {
      if (worker.joinable())
        worker.join();
    }
  }

  // 提交任务的模板函数
  // F: 函数类型, Args: 参数类型
  template <class F, class... Args>
  auto enqueue(F &&f, Args &&...args)
      -> std::future<typename std::result_of<F(Args...)>::type> {

    // 推导返回值类型
    using return_type = typename std::result_of<F(Args...)>::type;

    // 将函数和参数绑定，并封装进 packaged_task
    // 使用 shared_ptr 是因为 std::function 要求可复制，而 packaged_task
    // 仅可移动
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();
    {
      std::unique_lock<std::mutex> lock(queue_mutex_);

      // 如果线程池已经停止，禁止提交新任务
      if (stop_)
        throw std::runtime_error("enqueue on stopped ThreadPool");

      // 将任务放入队列
      // 这里 lambda 捕获了 task shared_ptr，并在执行时调用它
      tasks_.emplace([task]() { (*task)(); });
    }

    // 通知一个线程有新任务
    condition_.notify_one();
    return res;
  }

private:
  // 线程池工作线程
  std::vector<std::thread> workers_;
  // 任务队列
  std::queue<std::function<void()>> tasks_;

  // 同步互斥量和条件变量
  std::mutex queue_mutex_;
  std::condition_variable condition_;

  // 停止标志
  std::atomic<bool> stop_;
};

#endif
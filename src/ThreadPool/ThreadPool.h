//
// Created by shecannotsee on 2022/10/10.
//

#ifndef PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_SRC_THREADPOOL_THREADPOOL_H_
#define PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_SRC_THREADPOOL_THREADPOOL_H_

#include <functional>
#include <memory>
#include <future>
#include "../SafeQueue/SafeQueue.h"

namespace NoCpp14Standard{
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
  return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}
};//namespace NoCpp14Standard

namespace sheThreadPool {

class ThreadPool {
 private:
  SafeQueue<std::function<void()>> _task;// safe task queue
  std::mutex _thread_pool_mutex;
  std::condition_variable _condition_variable;
  std::vector<std::thread> _threads_array;
  int _thread_num;
  bool _loopOn;
 public:
  ThreadPool()
      : ThreadPool(8) {};

  explicit ThreadPool(const int& thread_num)
      : _thread_num(thread_num),
        _loopOn(true) {
    for(int i=0;i<_thread_num; ++i)
      _threads_array.emplace_back(&ThreadPool::worker,this);
  };

  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(_thread_pool_mutex);
      _loopOn = false;
    }
    _condition_variable.notify_all();
    for (std::thread& t:_threads_array)
      t.join();
  };
 private:
  void worker() {
    std::function<void()> task;
    std::mutex temp;
    // TODO:It is only used to be called
    //std::unique_lock<std::mutex> lock(temp);

    while (this->_loopOn || !(_task.empty()) ) {
      std::unique_lock<std::mutex> lock(temp);
      if (this->_task.popSuccess(task) )
        task();
      else
        this->_condition_variable.wait(lock);
    }
  }

 public:
  template<typename F, typename... Args>
  void submit(F&& f,Args&&... args) {
    auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    this->_task.push([task](){task();});
    this->_condition_variable.notify_one();
    printf("submit success.\n");
  }

  // TODO:need to return future result to get execution status
  bool empty_task() {
    return _task.empty();
  }

};

};//namespace sheThreadPool

#endif //PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_SRC_THREADPOOL_THREADPOOL_H_

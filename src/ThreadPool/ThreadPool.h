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
  std::mutex _mutex;
  std::condition_variable _condition_variable;
  std::vector<std::thread> _threads_array;
  int _thread_num;
  bool _loopOn;
 public:
  explicit ThreadPool(int thread_num)
      : _thread_num(thread_num),
        _loopOn(true) {
    for(int i=0;i<thread_num; ++i) {
      _threads_array.emplace_back([this](){
        // add workers
        std::function<void()> task;
        while (this->_loopOn) {
          std::unique_lock<std::mutex> lock(this->_mutex);
          if (this->_task.popSuccess(task))
            task();
          else
            this->_condition_variable.wait(lock);
        }
      });
    }
  };
  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(_mutex);
      _loopOn = false;
    }
    _condition_variable.notify_all();
    for (auto& t:_threads_array)
      t.join();
  };

 public:
  template<typename F, typename... Args>
  void submit(F&& f,Args&&... args) {
    auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    this->_task.push([task](){task();});
    this->_condition_variable.notify_all();
  }

};

};//namespace sheThreadPool

#endif //PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_SRC_THREADPOOL_THREADPOOL_H_

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
  typedef std::function<void()> _void_ptr_f;
 private:
  SafeQueue<_void_ptr_f> _task;// task queue
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
      _threads_array.emplace_back(&ThreadPool::work, this);
    }
  };
  ~ThreadPool() {
    _loopOn= false;
    for (auto& t:_threads_array)
      t.join();
  };
 public:
  void work() {
    _void_ptr_f work_work;
    // TODO:Need to add stop time
    while (_loopOn) {
      std::unique_lock<std::mutex> lock(_mutex);
      if (_task.empty()) {
        _condition_variable.wait(lock);
      }
      else {
        // TODO:do something
        if (_task.popSuccess(work_work))
          work_work();
      }
    }
  };

//  // TODO:decltype(f(args...))->decltype(std::forward<Function>(f)(std::forward<Args>(args)...))
//  template<typename F, typename... Args>
//  auto submit_task(F f, Args... args) -> std::future<decltype(f(args...))> {
//    std::function<decltype(f(args...))()> func =
//        std::bind(std::forward<F>(f), std::forward<Args>(args)...);
//
//    std::shared_ptr<std::packaged_task<decltype(f(args...)())>> task_ptr =
//          std::make_shared<std::packaged_task<decltype(f(args...)())>>(func);
//    _void_ptr_f element = [task_ptr]() ->_void_ptr_f {
//      (*task_ptr)();
//    };
//    _task.push(element);
//    _condition_variable.notify_one();
//    return task_ptr.get_future();
//  };//submit_task

  template<typename F, typename... Args>
  void she_submit(F&& f,Args&&... args) {
    std::function<decltype(f(args...)())> func =
        std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    _void_ptr_f element = [func](){func();};
    _task.push(element);
    _condition_variable.notify_one();
  }

};

};//namespace sheThreadPool

#endif //PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_SRC_THREADPOOL_THREADPOOL_H_

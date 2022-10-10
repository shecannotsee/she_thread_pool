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
 public:
  ThreadPool() {

  };
 public:
  void start() {
    _void_ptr_f work_work;
    bool loop;
    // TODO:Need to add stop time
    while (loopOn) {
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

  template<typename F, typename... Args>
  auto submit_task(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    std::function<decltype(f(args...))()> func =
        std::bind(std::forward<F>(f), std::forward<Args>(args)...);

    std::unique_ptr<std::packaged_task<decltype(f(args...)())>> task_ptr =
        NoCpp14Standard::make_unique<std::packaged_task<decltype(f(args...)())>>(func);
    //
    _void_ptr_f element = [task_ptr](){
      (*task_ptr)();
    };
    _task.push(element);
    // TODO:call sleep thread
    // do something...
    _condition_variable.notify_one();

    return task_ptr.get_future();
  };//submit
};

};//namespace sheThreadPool

#endif //PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_SRC_THREADPOOL_THREADPOOL_H_

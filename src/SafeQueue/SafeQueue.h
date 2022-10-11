//
// Created by shecannotsee on 2022/10/10.
//

#ifndef PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_SRC_SAFEQUEUE_SAFEQUEUE_H_
#define PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_SRC_SAFEQUEUE_SAFEQUEUE_H_

#include <queue>
#include <mutex>

namespace sheThreadPool {

template<typename T>
class SafeQueue {
 private:
  std::queue<T> _queue;
  std::mutex _mutex;
 public:
  SafeQueue() = default;
  ~SafeQueue() = default;
  SafeQueue(const SafeQueue&) = delete;
  SafeQueue& operator=(const SafeQueue&) = delete;
  SafeQueue(SafeQueue&&) = default;
  SafeQueue& operator=(SafeQueue&&) = default;
 public:
  void push(T element) {
    std::unique_lock<std::mutex> lock(_mutex);
    _queue.push(element);
  };

  bool popSuccess(T& temp) {
    std::unique_lock<std::mutex> lock(_mutex);
    if (_queue.empty())
      return false;
    temp = std::move(_queue.front());
    _queue.pop();
    return true;
  };

  bool empty() {
    std::unique_lock<std::mutex> lock(_mutex);
    return _queue.empty();
  };
};

};//namespace sheThreadPool

#endif //PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_SRC_SAFEQUEUE_SAFEQUEUE_H_

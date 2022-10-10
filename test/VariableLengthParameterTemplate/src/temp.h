//
// Created by shecannotsee on 2022/10/9.
//

#ifndef VLPT_TEST_TEST_SHETHREADPOOL_TEST_VARIABLELENGTHPARAMETERTEMPLATE_SRC_TEMP_H_
#define VLPT_TEST_TEST_SHETHREADPOOL_TEST_VARIABLELENGTHPARAMETERTEMPLATE_SRC_TEMP_H_

#include <stdio.h>
#include <iostream>
#include <queue>
#include <functional>
#include <future>
#include <thread>

namespace method1 {
typedef std::function<void()> callback;

template<typename F,typename... Args>
auto submit(F &&f, Args &&... args) ->std::future<decltype(f(args...))> {
  std::function<decltype(f(args...))()> func =
      std::bind(std::forward<F>(f), std::forward<Args>(args)...);
};


void main() {
  std::function<int(int,int)> f1 = [](int a, int b)->int {
    printf("%d + %d = %d\n",a,b,a+b);
    return a+b;
  };
  f1(9,9);

  std::thread a(f1,2,3);
  a.join();
}

};//namespace method1

#endif //VLPT_TEST_TEST_SHETHREADPOOL_TEST_VARIABLELENGTHPARAMETERTEMPLATE_SRC_TEMP_H_

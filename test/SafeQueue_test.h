//
// Created by shecannotsee on 2022/10/10.
//

#ifndef PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_TEST_SAFEQUEUE_TEST_TEMP_H_
#define PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_TEST_SAFEQUEUE_TEST_TEMP_H_

#include <iostream>
#include <SafeQueue/SafeQueue.h>

namespace SafeQueue_test{

void main() {
  sheThreadPool::SafeQueue<int> sq;
  int temp = 0;
  if (sq.popSuccess(temp))
    std::cout<<"pop success.\n";
  else
    std::cout<<"pop failed.\n";

  for (int i=0;i<20;++i)
    sq.push(static_cast<int>(i));

  int t;
  while (sq.popSuccess(t)) {
    std::cout<<t<<" ";
  }
  std::cout<<"\n";
}

};//namespace SafeQueue_test

#endif //PACKAGED_TASK_TEST_TEST_SHETHREADPOOL_TEST_SAFEQUEUE_TEST_TEMP_H_

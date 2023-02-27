//
// Created by shecannotsee on 2023/2/27.
//
#include <stdio.h>
#include <ThreadPool/ThreadPool.h>
#include <unistd.h>

void f1(int a) {
  printf("f1...%d...\n",a);
  sleep(1);
  printf("f1___%d...\n",a);
}

void f2() {
  printf("f2...\n");
  sleep(1);
  printf("f2___\n");
}

int main() {
  sheThreadPool::ThreadPool p(5);
  int a=10;
  for (int j=0;j<10;++j) {
    for (int i = j; i < j+8; ++i)
      p.submit(f1, i+j);
  }
  //while (!p.empty_task()) ;
  return 0;
};
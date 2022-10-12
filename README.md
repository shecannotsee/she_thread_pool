线程池是为了避免频繁的开辟和销毁线程而带来的额外开销，进而使用空间换时间在程序起始时创建多个线程并休眠。等待任务添加时线程休眠，

**伸缩性**：指线程数量的增大和减小



### 模式

1.生产者/消费者模式（该线程池为此种实现）

2.领导者/追随者模式：线程有三种类型：领导者，追随者和工作者。任务来临时，领导者从追随者中选出继任，然后转变成工作者处理任务，任务结束重新变为追随者等待下一个领导者选出继任

### 一般实现

1.线程池管理：TODO

2.工作线程：private:ThreadPool::work()

3.任务接口：submit()，将传入函数进行两层封装，添加到SafeQueue< std::function<void()> >中 

4.任务队列：SafeQueue< class >是对std::queue的线程安全封装

### How to ues?

example
```c++
#include "ThreadPool"

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

void main() {
  sheThreadPool::ThreadPool p(5);
  for (int i = 0; i < 8; ++i)
    p.submit(f1, i);
}
```


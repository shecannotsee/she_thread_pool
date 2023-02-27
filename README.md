sheThreadPool is a library for thread pool  based on c++11.

Authors: shecannotsee (shecannotsee@163.com)

# Features

- Based on c++11 and without any dependency
- Easy to use.
- Clear architecture so that you can easily modify the library



# Documentation

You can find more details in folder ./example

example.cpp

```c++
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
```



# Getting the Source

```shell
git clone https://github.com/shecannotsee/sheThreadPool.git
```



# Building

This project supports [CMake](https://cmake.org/) out of the box.

### Build for Linux or Mac

```shell
# now you are in the directory ${path}/sheThreadPool
➜ pwd
${path}/sheThreadPool
➜ mkdir build
➜ cd build
➜ cmake ..
➜ make
➜ make install
```

//
// Created by shecannotsee on 2022/10/9.
//

#ifndef VLPT_TEST_TEST_SHETHREADPOOL_TEST_STD_BIND_SRC_TEMP_H_
#define VLPT_TEST_TEST_SHETHREADPOOL_TEST_STD_BIND_SRC_TEMP_H_
#include <stdio.h>
#include <iostream>
#include <functional>
#include <memory>
namespace bll {
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts &&... params) {
  return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}
};//namespace bll
namespace method1 {

void f(int n1, int n2, int n3, int n4, int n5) {
  printf("%d,%d,%d,%d,%d\n",n1,n2,n3,n4,n5);
}
int get(int i) {
  return i;
}
class foo{
 private:
  int _num;
 public:
  int _data;
  foo(int num) {
    _num = num;
    _data = num;
    printf("foo create:\t%d.\n",num);
  }
  void add_display(int n1, int n2) {
    printf("\t:%d+%d = %d\n",n1,n2,n1+n2);
  }
  static void static_f(int i) {
    std::cout<<"static_f:\t"<<i<<".\n";
  }
};

void main() {
  using namespace  std::placeholders;
  std::cout<<"===================function test===================\n";
  int n = 999;
  // std::bind use value-pass
  // std::ref  like param&
  // std::cref like const param&
  auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);
  f1(1,2,1001,1002,1003,1004,1005);//f(2,42,1,10,10)
  auto f2 = std::bind(f, _3, std::bind(get,_2), _3, 444, 555);
  f2(10,11,12);//f(12,g(11),12,444,555)

  std::cout<<"===================class function test===================\n";
  foo test_class(100);
  auto f3 = std::bind(&foo::add_display, &test_class, _1, _2);
  f3(199,200);

  std::cout<<"===================class data test===================\n";
  auto f4 = std::bind(&foo::_data, _1);
  std::cout<<"class data is :\t"<<f4(test_class)<<"\n";

  std::cout<<"===================smart ptr test===================\n";
  std::cout<< f4(std::make_shared<foo>(test_class)) << '\n';
  std::cout<< f4(bll::make_unique<foo>(test_class)) << '\n';





}

};//namespace method1

#endif //VLPT_TEST_TEST_SHETHREADPOOL_TEST_STD_BIND_SRC_TEMP_H_

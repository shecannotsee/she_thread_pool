//
// Created by shecannotsee on 2022/10/9.
//

#ifndef VLPT_TEST_TEST_SHETHREADPOOL_TEST_STD_FUNCTION_SRC_TEMP_H_
#define VLPT_TEST_TEST_SHETHREADPOOL_TEST_STD_FUNCTION_SRC_TEMP_H_

#include <stdio.h>
#include <iostream>
#include <functional>

namespace method1 {
void print_num(int i) {
  printf("%d\n", i);
}
template<typename T>
void f(T a, T b) {
  std::cout<<a<<","<<b<<"\n";
}

class foo{
 private:
  int _num;
 public:
  int _data;
  foo(int num){
    _num = num;
    _data = num;
    printf("foo create:\t%d.\n",num);
  };
 public:
  void add_param(int add_num){
    printf("no const class function:\t%d+%d=%d\n",_num,add_num,_num+add_num);
    _num += add_num;
  };
  void print_num (int p) const {
    printf("const class function:\t_num:%d,send in param is:%d.\n",_num,p);
  }
  static void static_function() {
    printf("static function has been call.\n");
  };
};

void main() {
  std::cout<<"================normal function test================\n";
  std::function<void(int)> fp_print_num = print_num;
  fp_print_num(99);
  std::function<void(unsigned int,unsigned int)> f_p = f<unsigned int>;
  f_p(-1,-1);// 4294967295
  std::cout<<"================connect to std::bind test================\n";
  std::function<void()> fp_bind = std::bind(print_num,100);
  fp_bind();
  std::cout<<"================lambda test================\n";
  std::function<void()> fp_lambda = [](){printf("lambda.\n");};
  fp_lambda();
  std::cout<<"===============class function test================\n";
  std::function<void(const foo&, int)> f_class_public_with_const = &foo::print_num;
  const foo test_class_const(14159);
  f_class_public_with_const(test_class_const, 1);
  f_class_public_with_const(99999,1);// temp class(99999)
  std::function<void(foo&, int)> f_class_public_without_const = &foo::add_param;
  foo test_class_no_const(217);
  f_class_public_without_const(test_class_no_const,1);
  // f_class_public_without_const(88888,1);//error
  std::cout<<"===============class data test================\n";
  std::function<int(const foo&)> f_class_data = &foo::_data;
  printf("class(14159):\t%d.\n",f_class_data(test_class_const));
  printf("class(217):\t%d.\n",f_class_data(test_class_no_const));
  std::cout<<"===============class static function test===============\n";
  std::function<void()> f_class_static_function = foo::static_function;
  std::function<void()> f_class_static_function_ = &foo::static_function;
  f_class_static_function();
  f_class_static_function_();
  std::cout<<"================class with bind test================\n";
  using std::placeholders::_1;
  const foo bind_class_const(1000);
  std::function<void(int)> f_class_function_bind =                     std::bind(&foo::print_num, bind_class_const, _1);
  f_class_function_bind(10);
  std::function<void(int)> f_class_function_bind_with_reference =      std::bind(&foo::print_num,&bind_class_const, _1);
  f_class_function_bind_with_reference(11);
}
};//namespace method1

#endif //VLPT_TEST_TEST_SHETHREADPOOL_TEST_STD_FUNCTION_SRC_TEMP_H_

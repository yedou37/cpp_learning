#include <iostream>

// 测试类：无虚函数
class NoVirtual {
public:
  void func() { std::cout << "NoVirtual::func" << std::endl; }
  int data;
};

// 测试类：有虚函数
class WithVirtual {
public:
  virtual void func() { std::cout << "WithVirtual::func" << std::endl; }
  int data;
};

// 原始A类
class A {
public:
  virtual void funcA() { std::cout << "A::funcA" << std::endl; }
  int a_data;
};

// 非虚继承的情况
class ANonVirtual {
public:
  virtual void funcA() { std::cout << "ANonVirtual::funcA" << std::endl; }
  int a_data;
};

class BNonVirtual : public ANonVirtual {
public:
  virtual void funcB() { std::cout << "BNonVirtual::funcB" << std::endl; }
  int b_data;
};

// 原始继承结构
class B : virtual public A {
public:
  virtual void funcB() { std::cout << "B::funcB" << std::endl; }
  int b_data;
};

class C : virtual public A {
public:
  virtual void funcC() { std::cout << "C::funcC" << std::endl; }
  int c_data;
};

class D : public B, public C {
public:
  virtual void funcD() { std::cout << "D::funcD" << std::endl; }
  int d_data;
};

// 打印vptr地址的函数
template <typename T> void printVptr(const T &obj) {
  // 取对象首地址，强制转换为void**，因为vptr通常在对象开头
  void **vptr = (void **)&obj;
  std::cout << "vptr = " << vptr[0] << std::endl;
}

int main() {
  // 测试基本情况
  NoVirtual noVirtual;
  WithVirtual withVirtual;
  A a;
  ANonVirtual aNonVirtual;
  BNonVirtual bNonVirtual;
  D d;
  B b;
  C c;

  std::cout << "=== 大小信息 ===" << std::endl;
  std::cout << "sizeof(NoVirtual) = " << sizeof(NoVirtual) << std::endl;
  std::cout << "sizeof(WithVirtual) = " << sizeof(WithVirtual) << std::endl;
  std::cout << "sizeof(A) = " << sizeof(A) << std::endl;
  std::cout << "sizeof(ANonVirtual) = " << sizeof(ANonVirtual) << std::endl;
  std::cout << "sizeof(BNonVirtual) = " << sizeof(BNonVirtual) << std::endl;
  std::cout << "sizeof(B) = " << sizeof(B) << std::endl;
  std::cout << "sizeof(C) = " << sizeof(C) << std::endl;
  std::cout << "sizeof(D) = " << sizeof(D) << std::endl;

  std::cout << "\n=== 虚函数表指针 ===" << std::endl;
  std::cout << "WithVirtual对象的vptr: ";
  printVptr(withVirtual);

  std::cout << "A对象的vptr: ";
  printVptr(a);

  std::cout << "ANonVirtual对象的vptr: ";
  printVptr(aNonVirtual);

  std::cout << "BNonVirtual对象的vptr: ";
  printVptr(bNonVirtual);

  std::cout << "B对象的vptr: ";
  printVptr(b);

  std::cout << "C对象的vptr: ";
  printVptr(c);

  std::cout << "D对象的B部分vptr: ";
  printVptr(static_cast<B &>(d));

  std::cout << "D对象的C部分vptr: ";
  printVptr(static_cast<C &>(d));

  std::cout << "D对象的A部分vptr: ";
  printVptr(static_cast<A &>(d));

  std::cout << "\n=== 验证vptr存在性 ===" << std::endl;
  // 验证vptr是否真的存在
  std::cout << "WithVirtual对象首8字节: " << *(void **)&withVirtual
            << std::endl;
  std::cout << "A对象首8字节: " << *(void **)&a << std::endl;
  std::cout << "D对象中A部分首8字节: " << *(void **)(static_cast<A *>(&d))
            << std::endl;

  return 0;
}
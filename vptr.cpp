#include <iomanip>
#include <iostream>

class A {
public:
  virtual void funcA() { std::cout << "A::funcA" << std::endl; }
  virtual void funcA2() { std::cout << "A::funcA2" << std::endl; }
  int a_data;
};

class B : virtual public A {
public:
  virtual void funcB() { std::cout << "B::funcB" << std::endl; }
  virtual void funcB2() { std::cout << "B::funcB2" << std::endl; }
  int b_data;
};

class C : virtual public A {
public:
  virtual void funcC() { std::cout << "C::funcC" << std::endl; }
  virtual void funcC2() { std::cout << "C::funcC2" << std::endl; }
  int c_data;
};

class D : public B, public C {
public:
  void funcA() override { std::cout << "D::funcA" << std::endl; }
  void funcD() { std::cout << "D::funcD" << std::endl; }
  int d_data;
};

// 打印虚表内容
void printVTable(void **vptr, const char *name) {
  std::cout << "=== " << name << " 虚表 ===" << std::endl;
  for (int i = 0; i < 8; i++) {
    std::cout << "[" << i << "] " << std::hex << vptr[i] << std::dec
              << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  D d;

  // 获取B的vptr（D对象起始位置）
  void **vptr_B = *(void ***)&d;
  printVTable(vptr_B, "B的虚表");

  // 获取C的vptr（需要偏移）
  void **vptr_C = *(void ***)((char *)&d + 16);
  printVTable(vptr_C, "C的虚表");

  // 测试虚函数调用
  std::cout << "=== 虚函数调用测试 ===" << std::endl;
  B *pb = &d;
  C *pc = &d;
  A *pa = &d;

  pb->funcA(); // 应该调用D::funcA
  pc->funcA(); // 应该调用D::funcA
  pa->funcA(); // 应该调用D::funcA

  return 0;
}
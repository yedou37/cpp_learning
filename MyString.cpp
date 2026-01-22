#include <cstddef>
#include <cstring>
#include <iostream>
#include <utility>

class MyString {
public:
  MyString(const char *str = nullptr) {
    if (str == nullptr) {
      data_ = new char[1];
      *data_ = '\0';
      size_ = 0;
    } else {
      auto len = std::strlen(str) + 1;
      data_ = new char[len];
      std::memcpy(data_, str, len);
      size_ = len - 1;
    }
    std::cout << "default ctor\n";
  }
  MyString(const MyString &other) {
    size_ = other.size_;
    data_ = new char[size_ + 1];
    std::memcpy(data_, other.data_, size_ + 1);
    std::cout << "cpy ctor\n";
  }

  MyString &operator=(const MyString &rhs) {
    if (this == &rhs) {
      return *this;
    }
    char *new_data = new char[rhs.size_ + 1];
    std::memcpy(new_data, rhs.data_,
                rhs.size_ + 1); // 这里一定要先new 再delete 防止出现异常之后
                                // 原来的结构处于不可用的状态
    delete[] data_;
    size_ = rhs.size_;
    data_ = new_data;
    std::cout << "cpy assignment\n";
    return *this;
  }
  /*
    MyString &operator=(MyString rhs) {
      std::swap(data_, rhs.data_);
      std::cout << "cpy assignment \n";
      return *this;
    }
  */
  MyString(MyString &&other) noexcept : data_(nullptr), size_(0) {
    data_ = other.data_;
    size_ = other.size_;

    other.data_ = nullptr;
    other.size_ = 0;
    std::cout << "move ctor\n";
  }

  MyString &operator=(MyString &&rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }
    delete[] data_;
    data_ = rhs.data_;
    size_ = rhs.size_;

    rhs.data_ = nullptr;
    rhs.size_ = 0;
    std::cout << "move operator\n";
    return *this;
  }

  ~MyString() { delete[] data_; }
  size_t len() const {
    if (data_ == nullptr) {
      return 0;
    }
    return size_;
  }
  const char *c_str() const { return data_ == nullptr ? "" : data_; }
  char *data() { return data_; }
  friend std::ostream &operator<<(std::ostream &os, const MyString &ms) {
    os << ms.c_str();
    return os;
  }

private:
  char *data_;
  size_t size_;
};

int main() {
  MyString str1;
  MyString str2("Hello!");
  std::cout << str1 << " " << str2 << "\n";
  MyString str3 = std::move(str2);
  std::cout << str3 << "\n";
  MyString str4 = std::move(
      MyString("tmp str")); // 这里不显式调用move的话 会直接只有一个默认构造
                            // 类似编译器的RVO优化
  std::cout << str4 << "\n";
  return 0;
}
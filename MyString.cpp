#include <cstring>
#include <iostream>
#include <utility>

class MyString {
public:
  MyString(const char *str = nullptr) {
    if (str == nullptr) {
      data_ = new char[1];
      *data_ = '\0';
    } else {
      auto len = std::strlen(str) + 1;
      data_ = new char[len];
      std::memcpy(data_, str, len);
    }
    std::cout << "default ctor\n";
  }
  MyString(const MyString &other) {
    auto len = std::strlen(other.data_) + 1;
    data_ = new char[len];
    std::memcpy(data_, other.data_, len);
    std::cout << "cpy ctor\n";
  }
  /*
    MyString &operator=(MyString rhs) {
      std::swap(data_, rhs.data_);
      std::cout << "cpy assignment \n";
      return *this;
    }
  */
  MyString(MyString &&other) noexcept {
    data_ = other.data_;
    other.data_ = nullptr;
    std::cout << "move ctor \n";
  }

  MyString &operator=(MyString &&rhs) noexcept {
    if (rhs.data_ == this->data_) {
      return *this;
    }
    delete[] data_;
    data_ = rhs.data_;
    rhs.data_ = nullptr;
    std::cout << "move assignment\n";
    return *this;
  }

  ~MyString() { delete[] data_; }
  size_t len() const { return std::strlen(data_); }

  char *c_str() { return data_; }

private:
  char *data_;
};
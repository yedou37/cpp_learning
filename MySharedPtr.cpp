#include <atomic>
#include <cassert>
#include <cstddef>

template <class T> class MySharedPtr {
public:
  explicit MySharedPtr(T *ptr = nullptr) : ptr_(ptr) {
    if (ptr_ == nullptr) {
      ref_cnt_ = nullptr;
    } else {
      ref_cnt_ = new std::atomic<int>(1);
    }
  }

  ~MySharedPtr() { release(); }

  MySharedPtr(const MySharedPtr &other) {
    ref_cnt_ = other.ref_cnt_;
    ptr_ = other.ptr_;
    if (ref_cnt_ != nullptr) {
      ref_cnt_->fetch_add(1);
    }
  }

  MySharedPtr &operator=(const MySharedPtr &rhs) {
    if (this == &rhs) {
      return *this;
    }
    release();
    ref_cnt_ = rhs.ref_cnt_;
    ptr_ = rhs.ptr_;
    if (ref_cnt_ != nullptr) {
      ref_cnt_->fetch_add(1);
    }
    return *this;
  }

  MySharedPtr(MySharedPtr &&other) noexcept {
    ptr_ = other.ptr_;
    ref_cnt_ = other.ref_cnt_;
    other.ptr_ = nullptr;
    other.ref_cnt_ = nullptr;
  }

  MySharedPtr &operator=(MySharedPtr &&rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }
    release();
    ptr_ = rhs.ptr_;
    ref_cnt_ = rhs.ref_cnt_;
    rhs.ptr_ = nullptr;
    rhs.ref_cnt_ = nullptr;
    return *this;
  }

  T &operator*() const { return *ptr_; }
  T *operator->() const { return ptr_; }

  int use_count() const { return ref_cnt_ == nullptr ? 0 : ref_cnt_->load(); }

private:
  T *ptr_;
  std::atomic<int> *ref_cnt_;

  void release() {
    if (ref_cnt_ != nullptr) {
      if (ref_cnt_->fetch_sub(1) == 1) {
        delete ptr_;
        delete ref_cnt_;
      }
      ref_cnt_ = nullptr;
      ptr_ = nullptr;
    }
  }
};

int main() { return 0; }
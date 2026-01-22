#include <algorithm>
#include <atomic>
#include <cassert>
#include <climits>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
class CMS {
public:
  CMS(const size_t &depth, const size_t &width) : depth_(depth), width_(width) {
    matrix_ = std::make_unique<std::atomic<int>[]>(depth * width);
  }
  void Add(const std::string &key);
  auto Estimate(const std::string &key) const -> int;

private:
  std::unique_ptr<std::atomic<int>[]> matrix_;
  size_t depth_;
  size_t width_;
  auto GetHash(const std::string &key, const size_t &row_idx) const -> size_t;
};

void CMS::Add(const std::string &key) {
  for (size_t i = 0; i < depth_; i++) {
    size_t offset = i * width_;
    auto idx = GetHash(key, i) + offset;
    matrix_[idx].fetch_add(1, std::memory_order_relaxed);
  }
}
auto CMS::Estimate(const std::string &key) const -> int {
  int count = INT_MAX;
  for (size_t i = 0; i < depth_; i++) {
    size_t offset = i * width_;
    auto idx = GetHash(key, i) + offset;
    auto cur_count = matrix_[idx].load();
    count = std::min(cur_count, count);
  }
  return count;
}
auto CMS::GetHash(const std::string &key, const size_t &row_idx) const
    -> size_t {
  size_t h1 = std::hash<std::string>{}(key);
  size_t h2 = h1 * 0x5bd1e995;
  return (h1 + row_idx * h2) % width_;
}

void TestCMS() {
  CMS cms(20, 200);
  cms.Add("apple");
  cms.Add("apple");
  cms.Add("apple");
  cms.Add("banana");
  assert(cms.Estimate("apple") >= 3);
  std::cout << cms.Estimate("apple") << std::endl;
  assert(cms.Estimate("banana") >= 1);
  std::cout << cms.Estimate("banana") << std::endl;
  assert(cms.Estimate("orange") >= 0);
  std::cout << cms.Estimate("orange") << std::endl;
  auto thread_func = [&cms]() {
    for (int i = 0; i < 60; i++) {
      cms.Add("pear");
      cms.Add("grape");
    }
  };
  std::thread t1(thread_func);
  std::thread t2(thread_func);
  t1.join();
  t2.join();
  assert(cms.Estimate("pear") >= 120);
  std::cout << cms.Estimate("pear") << std::endl;
  assert(cms.Estimate("grape") >= 120);
  std::cout << cms.Estimate("grape") << std::endl;
}
int main() {
  TestCMS();
  return 0;
}
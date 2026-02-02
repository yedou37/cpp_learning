#include <cassert>

#include <list>
#include <unordered_map>

class LRUCache {
public:
  LRUCache(int capacity) : capacity_(capacity) {};

  int get(int key) {
    if (lru_map_.count(key)) {
      access(key);
      return lru_map_[key]->val_;
    }
    return -1;
  }

  void put(int key, int val) {
    if (lru_map_.count(key)) {
      access(key);
    } else {
      lru_.push_back({key, val});
      lru_map_[key] = std::prev(lru_.end());
      if (++size_ > capacity_) {
        lru_map_.erase(lru_.begin()->key_);
        lru_.erase(lru_.begin());
      }
    }
  }

private:
  struct node {
    int key_;
    int val_;
  };
  int capacity_;
  int size_{0};
  std::list<node> lru_;
  std::unordered_map<int, std::list<node>::iterator> lru_map_;

  void access(int key) { lru_.splice(lru_.end(), lru_, lru_map_[key]); }
};

void testLRU() {
  LRUCache c(2);
  c.put(1, 1);
  c.put(2, 2);
  assert(c.get(1) == 1);
  c.put(3, 3);
  assert(c.get(2) == -1);
  c.put(4, 4);
  assert(c.get(1) == -1);
  assert(c.get(3) == 3);
  assert(c.get(4) == 4);
}

int main() {
  testLRU();

  return 0;
}
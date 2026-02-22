#include <cassert>
#include <iostream>
#include <vector>

int binSearch(std::vector<int> &nums, int k) {
  int left = 0;
  int right = nums.size() - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] > k) {
      right = mid - 1;
    } else if (nums[mid] < k) {
      left = mid + 1;
    } else {
      return mid;
    }
  }
  return left;
}

int main() {
  std::vector vec{1, 2, 3, 5, 7, 10};
  assert(binSearch(vec, 4) == 3);
  assert(binSearch(vec, 3) == 2);
  std::cout << "ALL PASSED\n";
  return 0;
}
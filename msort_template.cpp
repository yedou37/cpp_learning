#include <cinttypes>
#include <iostream>
#include <utility>
#include <vector>

namespace MyMsort {

template <typename T>
void merge(std::vector<T> &arr, int left, int mid, int right,
           std::vector<T> &tmp) {
  for (int i = left; i <= right; i++) {
    tmp[i] = std::move(arr[i]);
  }
  int i = left;
  int j = mid + 1;
  for (int k = left; k <= right; k++) {
    if (j > right) {
      arr[k] = std::move(tmp[i++]);
    } else if (i > mid) {
      arr[k] = std::move(tmp[j++]);
    } else if (tmp[i] <= tmp[j]) {
      arr[k] = std::move(tmp[i++]);
    } else {
      arr[k] = std::move(tmp[j++]);
    }
  }
}

template <typename T>
void msort(std::vector<T> &arr, int left, int right, std::vector<T> &tmp) {
  if (left >= right) {
    return;
  }
  auto mid = left + (right - left) / 2;
  MyMsort::msort(arr, left, mid, tmp);
  MyMsort::msort(arr, mid + 1, right, tmp);
  MyMsort::merge(arr, left, mid, right, tmp);
}
template <typename T> void mergeSort(std::vector<T> &arr) {
  if (arr.empty()) {
    return;
  }
  std::vector<T> tmp(arr.size());
  MyMsort::msort(arr, 0, arr.size() - 1, tmp);
}

} // namespace MyMsort

int main() {
  std::vector<int> data = {34, 7, 23, 32, 5, 62, 32, 12, 0};

  std::cout << "Original: ";
  for (int x : data)
    std::cout << x << " ";
  std::cout << "\n";

  MyMsort::mergeSort(data);

  std::cout << "Sorted:   ";
  for (int x : data)
    std::cout << x << " ";
  std::cout << "\n";

  return 0;
}
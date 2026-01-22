#include <iostream>
#include <vector>

namespace MyQsort {

template <typename T> void qsort(std::vector<T> &arr, int left, int right) {
  if (left >= right) {
    return;
  }
  T pivot = arr[left + (right - left) / 2];
  int i = left - 1;
  int j = right + 1;
  while (i < j) {
    do
      i++;
    while (arr[i] < pivot);
    do
      j--;
    while (arr[j] > pivot);
    if (i < j) {
      std::swap(arr[i], arr[j]);
    }
  }
  qsort(arr, left, j);
  qsort(arr, j + 1, right);
}

template <typename T> void quickSort(std::vector<T> &arr) {
  if (arr.empty()) {
    return;
  }
  qsort(arr, 0, static_cast<int>(arr.size() - 1));
}
} // namespace MyQsort

int main() {
  std::vector<int> data = {34, 7, 23, 32, 5, 62, 32, 12, 0};

  std::cout << "Original: ";
  for (int x : data)
    std::cout << x << " ";
  std::cout << "\n";

  MyQsort::quickSort(data);

  std::cout << "Sorted:   ";
  for (int x : data)
    std::cout << x << " ";
  std::cout << "\n";

  return 0;
}
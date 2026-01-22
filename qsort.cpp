#include <iostream>
#include <vector>
namespace MyQsort {
void qsort(std::vector<int> &arr, int left, int right) {
  if (left >= right) {
    return;
  }
  int pivot = arr[left + (right - left) / 2];
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

void quickSort(std::vector<int> &arr) {
  if (arr.empty()) {
    return;
  }
  MyQsort::qsort(arr, 0, arr.size() - 1);
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
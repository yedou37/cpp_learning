#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
bool dfs(std::vector<int> &nums, std::string &track, std::string &target,
         bool isLess, int start) {

  if (track.length() == target.size()) {
    return isLess;
  }
  for (const auto &n : nums) {
    if (!isLess && n > (target[start] - '0')) {
      continue;
    }
    track.push_back('0' + n);
    if (dfs(nums, track, target, isLess || n < (target[start] - '0'),
            start + 1)) {
      return true;
    }
    track.pop_back();
  }
  return false;
}

std::string solve(std::vector<int> &nums, int t) {
  std::string track{};
  auto target = std::to_string(t);
  if (dfs(nums, track, target, false, 0)) {
    return track;
  }
  if (target.length() > 1) {
    return std::string(target.length() - 1, nums.front() + '0');
  }
  return {};
}

int main() {
  std::vector nums{1, 2, 6, 7, 9};
  auto cmp = [](auto a, auto b) { return a > b; };
  std::sort(nums.begin(), nums.end(), cmp);
  std::cout << solve(nums, 112) << std::endl;
  std::cout << solve(nums, 999) << std::endl;
  return 0;
}
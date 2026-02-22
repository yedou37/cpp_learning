#include <cassert>
#include <climits>
#include <iostream>
#include <vector>
int coinChange(std::vector<int> &coins, int amount) {
  std::vector<int> dp(amount + 1, INT_MAX - 1);
  dp[0] = 0;
  for (int i = 1; i <= amount; i++) {
    for (const int &c : coins) {
      if ((i - c) >= 0) {
        dp[i] = std::min(dp[i], dp[i - c] + 1);
      }
    }
  }
  return dp[amount] == INT_MAX - 1 ? -1 : dp[amount];
}
int main() {
  std::vector<int> coins{1, 2, 5, 10};
  assert(coinChange(coins, 10) == 1);
  assert(coinChange(coins, 12) == 2);
  coins = {2, 5, 10};
  assert(coinChange(coins, 3) == -1);
  std::cout << "all test passed!\n";
  return 0;
}
#include <condition_variable>
#include <iostream>
#include <stop_token>
#include <thread>
#include <vector>
std::mutex mu;
std::condition_variable cv;
int turn{0};
int cur{1};
void printFunc(std::stop_token st, int tid) {
  while (!st.stop_requested()) {
    std::unique_lock lck(mu);
    cv.wait_for(lck, std::chrono::milliseconds(100),
                [&st, &tid]() { return turn == tid || st.stop_requested(); });
    if (st.stop_requested() || cur >= 1000) {
      break;
    }
    std::cout << "thread[" << tid << "] print: " << cur++ << std::endl;
    turn++;
    turn %= 4;
    cv.notify_all();
  }
}

int main() {
  std::vector<std::jthread> threads;
  for (int i = 0; i < 4; i++) {
    threads.emplace_back(printFunc, i);
  }

  std::this_thread::sleep_for(std::chrono::seconds(2));
  for (int i = 0; i < 4; i++) {
    threads[i].request_stop();
  }
  cv.notify_all();
  return 0;
}
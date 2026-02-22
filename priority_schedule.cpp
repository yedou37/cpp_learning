#include <iostream>
#include <queue>
#include <string>
#include <vector>

// 任务结构体
typedef struct Task {
  int id;           // 任务ID
  int priority;     // 优先级（数字越大，优先级越高）
  int burstTime;    // 执行时间
  std::string name; // 任务名称

  Task(int i, int p, int b, const std::string &n)
      : id(i), priority(p), burstTime(b), name(n) {}

} Task;

// 自定义比较器，用于优先队列
class TaskComparator {
public:
  bool operator()(const Task &t1, const Task &t2) {
    // 优先级高的任务排在前面
    return t1.priority < t2.priority;
  }
};

class PrioritySchedule {
private:
  std::priority_queue<Task, std::vector<Task>, TaskComparator> taskQueue;

public:
  // 添加任务
  void addTask(int id, int priority, int burstTime, const std::string &name) {
    Task task(id, priority, burstTime, name);
    taskQueue.push(task);
    std::cout << "Added task: " << name << " (ID: " << id
              << ", Priority: " << priority << ", Burst Time: " << burstTime
              << ")" << std::endl;
  }

  // 执行调度
  void schedule() {
    std::cout << "\nScheduling tasks based on priority..." << std::endl;

    int totalTime = 0;

    // 按优先级执行任务
    while (!taskQueue.empty()) {
      Task currentTask = taskQueue.top();
      taskQueue.pop();

      std::cout << "Executing task: " << currentTask.name
                << " (ID: " << currentTask.id
                << ", Priority: " << currentTask.priority
                << ", Burst Time: " << currentTask.burstTime << ")"
                << std::endl;

      // 模拟任务执行
      totalTime += currentTask.burstTime;
      std::cout << "Task " << currentTask.name
                << " completed at time: " << totalTime << std::endl;
    }

    std::cout << "\nAll tasks completed. Total execution time: " << totalTime
              << std::endl;
  }

  // 获取队列大小
  int getQueueSize() const { return taskQueue.size(); }
};

int main() {
  PrioritySchedule scheduler;

  // 添加测试任务
  scheduler.addTask(1, 5, 10, "Task A");
  scheduler.addTask(2, 1, 5, "Task B");
  scheduler.addTask(3, 3, 8, "Task C");
  scheduler.addTask(4, 7, 12, "Task D");
  scheduler.addTask(5, 2, 6, "Task E");

  // 执行调度
  scheduler.schedule();

  return 0;
}
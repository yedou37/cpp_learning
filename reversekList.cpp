#include <iostream>

struct ListNode {
  int val_;
  ListNode *next_{nullptr};
  ListNode() : val_(-1), next_(nullptr) {}
  ListNode(int val) : val_(val), next_(nullptr) {}

  ListNode(int val, ListNode *next) : val_(val), next_(next) {}
};

ListNode *reverseList(ListNode *head) {
  if (head == nullptr) {
    return head;
  }
  ListNode *cur = head;
  ListNode *prev = nullptr;
  ListNode *next = head;
  while (cur != nullptr) {
    next = cur->next_;
    cur->next_ = prev;
    prev = cur;
    cur = next;
  }
  return prev;
}

ListNode *reverseKList(ListNode *head, int k) {
  auto *dummy = new ListNode();
  dummy->next_ = head;
  auto *pre = dummy;
  auto *end = dummy;
  auto *start = dummy;
  auto *nextGroup = dummy;
  while (end->next_ != nullptr) {
    for (int i = 0; i < k; i++) {
      end = end->next_;
    }
    if (end == nullptr) {
      break;
    }
    start = pre->next_;
    nextGroup = end->next_;
    end->next_ = nullptr;
    pre->next_ = reverseList(start);
    start->next_ = nextGroup;
    pre = start;
    end = start;
  }
  return dummy->next_;
}

int main() {
  auto *a = new ListNode(1);
  auto *b = new ListNode(2, a);
  auto *c = new ListNode(3, b);
  auto *d = new ListNode(4, c);
  auto *e = new ListNode(5, d);
  auto *p = e;
  while (p != nullptr) {
    std::cout << p->val_ << " ";
    p = p->next_;
  }
  auto *head = reverseList(e);
  p = head;
  std::cout << std::endl;
  while (p != nullptr) {
    std::cout << p->val_ << " ";
    p = p->next_;
  }

  auto *new_head = reverseKList(head, 2);
  p = new_head;
  std::cout << std::endl;
  while (p != nullptr) {
    std::cout << p->val_ << " ";
    p = p->next_;
  }
  std::cout << std::endl;
  return 0;
}
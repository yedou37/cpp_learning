#pragma once

class Singleton {
public:
  static Singleton &getInstance() {
    static Singleton instance;
    return instance;
  }
  Singleton(const Singleton &rhs) = delete;
  Singleton &operator=(const Singleton &rhs) = delete;

private:
  Singleton() {}
};
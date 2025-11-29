#pragma DAY01_SOLUTION_HPP

#include "logger/logger.hpp"

int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int multiply(int a, int b) { return a * b; }

int *divide(int a, int b) {
  if (b == 0) {
    Log::errorf("Division by zero error.");
    return nullptr;
  }
  return new int(a / b);
}

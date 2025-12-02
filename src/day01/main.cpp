#include "logger/logger.hpp"
#include "solution.hpp"
#include <string>
#include <vector>

int main() {
  auto lines = Reader("input_d1.txt");
  int z = RunWithZeroCount(lines);
  Log::debugf("s1: {}", z);

  auto lines2 = Reader("input_d1.txt");
  int z2 = RunWithPassthroughZeroCount(lines2);
  Log::debugf("s2: {}", z2);

  return 0;
}

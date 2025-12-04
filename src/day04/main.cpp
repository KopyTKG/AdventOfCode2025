#include "logger/logger.hpp"
#include "solution.hpp"
#include <vector>

int main() {
  std::vector<PaperRoll> rolls;
  FindRolls("input_d4.txt", rolls);
  Log::infof("Rolls with < 4 neighbors: {}", NeighborsL(rolls, 4));

  int count = CountValidRolls("input_d4.txt");
  Log::infof("Rolls with < 4 neighbors: {}", count);
  return 0;
}

#include "logger/logger.hpp"
#include "solution.hpp"
#include <thread>

void Start1() {
  std::vector<double> IDs;
  Parser("input_d2.txt", IDs);
  double sum = SumIDs(IDs);
  Log::infof("The sum of all valid IDs is: {}", sum);
}

void Start2() {
  std::vector<double> IDs;
  ParserStrict("input_d2.txt", IDs);
  double sum = SumIDs(IDs);
  Log::infof("The sum of all valid IDs is: {}", sum);
}

int main() {
  std::thread t1(Start1);
  std::thread t2(Start2);

  t1.join();
  t2.join();

  return 0;
}

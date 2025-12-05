#include "logger/logger.hpp"

#include "solution.hpp"

int main() {
  vector<long> foodDatabase;
  collectFoods("input_d5.txt", foodDatabase);
  Log::infof("Number of valid food items: {}", foodDatabase.size());

  auto i = countFreshIDs("input_d5.txt");
  Log::infof("Number of fresh food items: {}", i);
  return 0;
}

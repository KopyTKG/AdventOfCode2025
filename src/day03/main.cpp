#include "logger/logger.hpp"
#include "solution.hpp"

int main() {
  double output = 0;
  JoltageS1("input_d3.txt", output);
  Log::infof("The final output is: {}", output);
  output = 0;
  JoltageS2("input_d3.txt", output);
  Log::infof("The final output for star 2 is: {}", output);
  return 0;
}

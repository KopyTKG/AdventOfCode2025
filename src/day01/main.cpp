#include "logger/logger.hpp"

int main() {
  Log::infof("Application started.");
  Log::warnf("This is a warning message.");
  Log::errorf("This is an error message.");
  return 0;
}

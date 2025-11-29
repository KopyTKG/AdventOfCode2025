#include "logger/logger.hpp"

int main(int argc, char *argv[]) {
  Log::getInstance()->setLogLevel(Level::DEBUG);
  Log::getInstance()->setLogToConsole(true);
  Log::getInstance()->setLogToFile(false);

  Log::infoln("Setup is working!");

  return 0;
}

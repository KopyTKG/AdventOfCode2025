#pragma DAY01_SOLUTION_HPP

#include "logger/logger.hpp"
#include <filesystem>
#include <string>
#include <vector>

const int MIN = 0;
const int MAX = 100;
const int START = 50;

int turnLeft(int steps, int *pointer) {
  bool tdc = (*pointer == MIN);
  *pointer -= steps;

  int passthrough = 0;
  while (*pointer < MIN) {
    *pointer += MAX;
    passthrough++;
  }

  if (tdc && passthrough > MIN) {
    passthrough--;
  }
  return passthrough;
}

int turnRight(int steps, int *pointer) {
  *pointer += steps;

  int passthrough = 0;
  while (*pointer >= MAX) {
    *pointer -= MAX;
    passthrough++;
  }
  if (*pointer == MIN && passthrough > MIN) {
    passthrough--;
  }

  return passthrough;
}

enum class Directions : uint8_t {
  LEFT,
  RIGHT,
};

struct Line {
  Directions dir;
  int steps;
};

Line ParseLine(std::string line) {
  Line tmp;
  std::string n = "";
  for (const char c : line) {
    if (c == 'L')
      tmp.dir = Directions::LEFT;
    else if (c == 'R')
      tmp.dir = Directions::RIGHT;
    else
      n += c;
  }
  int steps = std::stoi(n);
  tmp.steps = steps;
  return tmp;
}

std::vector<Line> Reader(std::string filename) {
  std::string line;
  std::ifstream file;
  file.open(filename);
  if (!file.is_open()) {
    Log::errorf("!!! FATAL ERROR: Could not open file at: {}", filename);
    Log::errorf("!!! The computer is looking inside: {}",
                std::filesystem::current_path().string());
    Log::errorf("!!! It tried to find: {}",
                std::filesystem::absolute(filename).string());
    return {};
  }

  std::vector<Line> lines;
  while (std::getline(file, line)) {
    lines.push_back(ParseLine(line));
  }
  return lines;
}

int RunWithZeroCount(std::vector<Line> lines) {
  int zeros = 0;
  int cursor = START;
  for (Line l : lines) {
    if (l.dir == Directions::LEFT)
      turnLeft(l.steps, &cursor);
    else if (l.dir == Directions::RIGHT)
      turnRight(l.steps, &cursor);
    if (cursor == 0)
      zeros++;
  }
  return zeros;
}

int RunWithPassthroughZeroCount(std::vector<Line> lines) {
  int zeros = 0;
  int cursor = START;
  for (Line l : lines) {
    if (l.dir == Directions::LEFT) {
      int z = turnLeft(l.steps, &cursor);
      zeros += z;
    } else if (l.dir == Directions::RIGHT) {
      zeros += turnRight(l.steps, &cursor);
    }
    if (cursor == 0)
      zeros++;
  }
  return zeros;
}

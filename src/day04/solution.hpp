#pragma DAY04_SOLUTION_HPP
#pragma once

#include "global/global.hpp"
#include "logger/logger.hpp"

#include <string>
#include <vector>

using namespace std;

struct PaperRoll {
  int x, y;
  int neighbors;
};

void FindRolls(string filename, vector<PaperRoll> &rolls) {
  auto lines = GLB::Reader(filename);

  for (int y = 0; y < lines.size(); y++) {
    for (int x = 0; x < lines[y].size(); x++) {
      if (lines[y][x] == '@') {
        PaperRoll roll;
        roll.x = x;
        roll.y = y;
        roll.neighbors = 0;

        // Check neighbors
        for (int dy = -1; dy <= 1; dy++) {
          for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0)
              continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < lines[y].size() && ny >= 0 &&
                ny < lines.size()) {
              if (lines[ny][nx] == '@') {
                roll.neighbors++;
              }
            }
          }
        }

        rolls.push_back(roll);
      }
    }
  }
}

int NeighborsEQ(const vector<PaperRoll> &rolls, int neighborCount) {
  int count = 0;
  for (const auto &roll : rolls) {
    if (roll.neighbors == neighborCount) {
      count++;
    }
  }
  return count;
}

int NeighborsLEQ(const vector<PaperRoll> &rolls, int neighborCount) {
  int count = 0;
  for (const auto &roll : rolls) {
    if (roll.neighbors <= neighborCount) {
      count++;
    }
  }
  return count;
}

int NeighborsL(const vector<PaperRoll> &rolls, int neighborCount) {
  int count = 0;
  for (const auto &roll : rolls) {
    if (roll.neighbors < neighborCount) {
      count++;
    }
  }
  return count;
}

void PrintField(const vector<string> &lines) {
  for (const auto &line : lines) {
    Log::infof("{}", line);
  }
}

int CountValidRolls(string filename) {
  auto lines = GLB::Reader(filename);

  bool unchanged = true;
  int count = 0;

  int iteration = 0;
  while (unchanged) {
    unchanged = false;
    for (int y = 0; y < lines.size(); y++) {
      for (int x = 0; x < lines[y].size(); x++) {
        if (lines[y][x] == '@') {
          PaperRoll roll;
          roll.x = x;
          roll.y = y;
          roll.neighbors = 0;

          // Check neighbors
          for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
              if (dx == 0 && dy == 0)
                continue;
              int nx = x + dx;
              int ny = y + dy;
              if (nx >= 0 && nx < lines[y].size() && ny >= 0 &&
                  ny < lines.size()) {
                if (lines[ny][nx] == '@') {
                  roll.neighbors++;
                }
              }
            }
          }

          if (roll.neighbors < 4) {
            lines[y][x] = '.';
            unchanged = true;
            count++;
          }
        }
      }
    }
  }
  return count;
}

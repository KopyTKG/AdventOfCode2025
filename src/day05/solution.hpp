#pragma DAY05_SOLUTION_HPP
#pragma once

#include "global/global.hpp"
#include "logger/logger.hpp"

#include <vector>

using namespace std;

struct Range {
  long start;
  long end;

  bool operator<(const Range &other) const { return start < other.start; }
};

void collectFoods(std::string filename, vector<long> &foodDatabase) {
  auto lines = GLB::Reader(filename);
  vector<Range> valid = {};
  for (const auto &line : lines) {
    if (line.empty()) {
      continue;
    }
    auto parts = GLB::str_split(line, "-");
    if (parts.size() >= 2) {
      long startId = std::stol(parts[0]);
      long endId = std::stol(parts[1]);
      valid.push_back(Range{startId, endId});

    } else {
      long foodId = std::stol(line);
      for (auto range : valid) {
        if (foodId >= range.start && foodId <= range.end) {
          foodDatabase.push_back(foodId);
          break;
        }
      }
    }
  }
}

uint64_t countFreshIDs(std::string filename) {
  std::vector<std::string> lines = GLB::Reader(filename);

  std::vector<Range> ranges;
  ranges.reserve(lines.size());

  for (const auto &line : lines) {
    if (line.empty())
      continue;

    size_t dashPos = line.find('-');
    if (dashPos != std::string::npos) {
      try {
        long s = std::stol(line.substr(0, dashPos));
        long e = std::stol(line.substr(dashPos + 1));

        if (s > e)
          continue;

        ranges.push_back({s, e});
      } catch (...) {
        continue;
      }
    }
  }

  std::sort(ranges.begin(), ranges.end());

  std::vector<Range> merged;
  if (!ranges.empty()) {
    merged.push_back(ranges[0]);
    for (size_t i = 1; i < ranges.size(); ++i) {
      Range &current = merged.back();
      Range &next = ranges[i];

      if (next.start <= current.end + 1) {
        current.end = std::max(current.end, next.end);
      } else {
        merged.push_back(next);
      }
    }
  }

  uint64_t total_count = 0;
  for (const auto &r : merged) {
    total_count += (uint64_t)(r.end - r.start + 1);
  }

  return total_count;
}

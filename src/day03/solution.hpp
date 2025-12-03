#include <cmath>
#include <string>
#pragma DAY03_SOLUTION_HPP
#pragma once

#include "global/global.hpp"
#include "logger/logger.hpp"
#include <cstdlib>

using namespace std;

void JoltageS1(const string filename, double &output) {
  auto data = GLB::Reader(filename);
  for (auto line : data) {
    double f = -1, b = -1, l = -1;
    double loc = 0, lastKnown = 0;
    for (double i = 0; i < line.size() - 1; i++) {
      const double c{std::stod(string(1, line[i]))};
      if (c > f) {
        if (c != -1) {
          l = c;
          lastKnown = loc;
        }
        f = c;
        loc = i;
      }
      if (c == f && c == 9) {
        loc = i;
        break;
      }
    }
    for (double i = loc + 1; i < line.size(); i++) {
      const double c{std::stod(string(1, line[i]))};
      if (c > b)
        b = c;
    }
    output += (f * 10) + b;
  }
}

void JoltageS2(const string filename, double &output) {
  auto data = GLB::Reader(filename);
  for (auto line : data) {
    double jolts[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    double offset = 0, cap = 11;
    for (int jp = 0; jp < 12; jp++) {
      for (int i = offset; i < line.size() - cap; i++) {
        double current = std::atoi(string(1, line[i]).c_str());
        if (current > jolts[jp]) {
          jolts[jp] = current;
          offset = i + 1;
        }
      }
      cap--;
    }
    for (int j = 0; j < 12; j++) {
      output += jolts[j] * std::pow(10, 11 - j);
    }
  }
}

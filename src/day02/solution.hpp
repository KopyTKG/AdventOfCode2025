#pragma DAY02_SOLUTION_HPP
#pragma once

#include "global/global.hpp"
#include "logger/logger.hpp"
#include <regex>
#include <string>

bool isValid(std::string id) {
  std::regex rgx("^(\\d+)\\1$");
  return std::regex_match(id, rgx);
}

bool isValidStrict(std::string id) {
  std::regex rgx("^(\\d+)\\1+$");
  return std::regex_match(id, rgx);
}

void Parser(std::string filename, std::vector<double> &IDs) {
  auto data = GLB::Reader(filename);
  for (auto line : data) {
    auto items = GLB::str_split(line, ",");
    for (auto i : items) {
      auto range = GLB::str_split(i, "-");
      double start = std::stod(range[0]);
      double end = std::stod(range[1]);
      for (double id = start; id <= end; id++) {
        if (isValid(GLB::str_split(std::to_string(id), ".")[0])) {
          IDs.push_back(id);
        }
      }
    }
  }
}

void ParserStrict(std::string filename, std::vector<double> &IDs) {
  auto data = GLB::Reader(filename);
  for (auto line : data) {
    auto items = GLB::str_split(line, ",");
    for (auto i : items) {
      auto range = GLB::str_split(i, "-");
      double start = std::stod(range[0]);
      double end = std::stod(range[1]);
      for (double id = start; id <= end; id++) {
        if (isValidStrict(GLB::str_split(std::to_string(id), ".")[0])) {
          IDs.push_back(id);
        }
      }
    }
  }
}

double SumIDs(const std::vector<double> &IDs) {
  double sum = 0;
  for (auto id : IDs) {
    sum += id;
  }
  return sum;
}

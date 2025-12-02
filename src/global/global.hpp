#pragma GLOBAL_HPP
#pragma once

#include "logger/logger.hpp"
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace GLB {

vector<string> Reader(string filename) {
  string line;
  ifstream file;
  file.open(filename);
  if (!file.is_open()) {
    Log::errorf("!!! FATAL ERROR: Could not open file at: {}", filename);
    Log::errorf("!!! The computer is looking inside: {}",
                filesystem::current_path().string());
    Log::errorf("!!! It tried to find: {}",
                filesystem::absolute(filename).string());
    return {};
  }

  vector<string> lines;
  while (getline(file, line)) {
    lines.push_back(line);
  }
  return lines;
}

vector<string> str_split(string input, string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<std::string> res;

  while ((pos_end = input.find(delimiter, pos_start)) != std::string::npos) {
    token = input.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(input.substr(pos_start));
  return res;
}

} // namespace GLB

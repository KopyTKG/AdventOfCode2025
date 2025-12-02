#include <catch2/catch_test_macros.hpp>

#include "solution.hpp"
#include <string>
#include <vector>

TEST_CASE("Turn left test", "[logic]") {
  int start = 0;
  turnLeft(1, start);
  REQUIRE(start == 99);
}

TEST_CASE("Turn right test", "[logic]") {
  int start = 99;
  turnRight(1, start);
  REQUIRE(start == 0);
}

TEST_CASE("Turn left overflow test", "[overflow]") {
  int start = 0;
  turnLeft(101, start);
  REQUIRE(start == 99);
}

TEST_CASE("Turn right overflow test", "[overflow]") {
  int start = 99;
  turnRight(101, start);
  REQUIRE(start == 0);
}

TEST_CASE("Parse line test", "[logic]") {
  std::string line = "L95";
  Line l;
  l.dir = Directions::LEFT;
  l.steps = 95;
  Line x = ParseLine(line);
  REQUIRE(x.steps == l.steps);
  REQUIRE(x.dir == l.dir);
}

TEST_CASE("Run test data", "[run]") {
  auto lines = Reader(std::string(TEST_DATA_DIR) + "test_d1.txt");
  int z = RunWithZeroCount(lines);
  REQUIRE(z == 3);
}

TEST_CASE("Run test with passthrough count data", "[run]") {
  auto lines = Reader(std::string(TEST_DATA_DIR) + "test_d1.txt");
  int z = RunWithPassthroughZeroCount(lines);
  REQUIRE(z == 6);
}

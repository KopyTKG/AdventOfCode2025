#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "solution.hpp"

TEST_CASE("Test parser", "[logic]") {
  std::vector<PaperRoll> rolls;
  FindRolls(std::string(TEST_DATA_DIR) + "test_d4.txt", rolls);
  REQUIRE(NeighborsL(rolls, 4) == 13);
}

TEST_CASE("Test parser with replace", "[logic]") {
  int count = CountValidRolls(std::string(TEST_DATA_DIR) + "test_d4.txt");
  REQUIRE(count == 43);
}

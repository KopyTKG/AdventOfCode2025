#include <catch2/catch_test_macros.hpp>

#include "solution.hpp"

TEST_CASE("Test parser", "[logic]") {
  double output;
  JoltageS1(std::string(TEST_DATA_DIR) + "test_d3.txt", output);
  REQUIRE(output == 357);
}

TEST_CASE("Test parser star 2", "[logic]") {
  double output;
  JoltageS2(std::string(TEST_DATA_DIR) + "test_d3.txt", output);
  REQUIRE(output == 3121910778619.0);
}

#include <catch2/catch_test_macros.hpp>

#include "solution.hpp"

TEST_CASE("Test Database class addFood", "[logic]") {
  vector<long> foodDatabase;
  collectFoods(std::string(TEST_DATA_DIR) + "test_d5.txt", foodDatabase);
  REQUIRE(foodDatabase.size() == 3);
}

TEST_CASE("Test Star2 logic", "[logic]") {
  auto i = countFreshIDs(std::string(TEST_DATA_DIR) + "test_d5.txt");
  REQUIRE(i == 14);
}

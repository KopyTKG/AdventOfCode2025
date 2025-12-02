#include <catch2/catch_test_macros.hpp>

#include "solution.hpp"

TEST_CASE("Test isValid", "[logic]") {
  REQUIRE(isValid("111111") == true);
  REQUIRE(isValid("123456") == false);
  REQUIRE(isValid("222222") == true);
  REQUIRE(isValid("123123") == true);
  REQUIRE(isValid("123124") == false);
  REQUIRE(isValid("999") == false);
  REQUIRE(isValid("123123123") == false);
}

TEST_CASE("Test Parser and SumIDs", "[logic]") {
  std::vector<double> IDs;
  Parser(std::string(TEST_DATA_DIR) + "test_d2.txt", IDs);
  double sum = SumIDs(IDs);
  Log::debugf("{}", sum);
  REQUIRE(sum == 1227775554);
}

TEST_CASE("Test Strict Parser and SumIDs", "[logic]") {
  std::vector<double> IDs;
  ParserStrict(std::string(TEST_DATA_DIR) + "test_d2.txt", IDs);
  double sum = SumIDs(IDs);
  Log::debugf("{}", sum);
  REQUIRE(sum == 4174379265);
}

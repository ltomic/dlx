#include "gtest/gtest.h"
#include "dlx.hpp"

#include <vector>
#include <string>

namespace {
  TEST(TestBrute, SingleSolution_1) {
    std::vector<std::string> input = {
      "1001001",
      "1001000",
      "0001101",
      "0010110",
      "0110011",
      "0100001"
    };

    auto brute_sol = brute(input);
    std::vector<std::vector<int>> correct = {{1, 3, 5}};
    EXPECT_EQ(brute_sol, correct);
  }

  TEST(TestBrute, SingleSolution_2) {
    std::vector<std::string> input = {
      "101010000",
      "100001100",
      "010100000",
      "010001010",
      "000010011",
      "000001011",
      "000100101"
    };

    std::vector<std::vector<int>> correct_solution = {{0, 3, 6}};
    EXPECT_EQ(correct_solution, brute(input));
  }

  TEST(TestBrute, NoSolution_1) {
    std::vector<std::string> input = { "0" };
    
    std::vector<std::vector<int>> correct_solution;
    EXPECT_EQ(correct_solution, brute(input));
  }

  TEST(TestBrute, EveryRowSolution) {
    std::vector<std::string> input = {
      "11111",
      "11111",
      "11111",
      "11111"
    };


    std::vector<std::vector<int>> correct_solution = {{0}, {1}, {2}, {3}};

    EXPECT_EQ(correct_solution, brute(input));
  }

  TEST(TestBrute, EveryRowInSingleSolution) {
    std::vector<std::string> input = {
      "10000",
      "00100",
      "01000",
      "00001",
      "00010"
    };

    std::vector<std::vector<int>> correct_solution = {{0, 1, 2, 3, 4}};
    EXPECT_EQ(correct_solution, brute(input));
  }
  
  TEST(SmallTest, SingleSolution) {
    std::vector<std::string> input = {
      "1001001",
      "1001000",
      "0001101",
      "0010110",
      "0110011",
      "0100001"
    };

    std::vector<std::vector<int>> sols = solve(input);
    std::vector<std::vector<int>> correct = {{1, 3, 5}};
    EXPECT_EQ(sols, correct);
  }  

  TEST(SmallTest, SingleSolution_2) {
    std::vector<std::string> input = {
      "101010000",
      "100001100",
      "010100000",
      "010001010",
      "000010011",
      "000001011",
      "000100101"
    };

    std::vector<std::vector<int>> correct_solution = {{0, 3, 6}};
    EXPECT_EQ(correct_solution, solve(input));
  }

  TEST(SmallTest, NoSolution_1) {
    std::vector<std::string> input = { "0" };
    
    std::vector<std::vector<int>> correct_solution;
    EXPECT_EQ(correct_solution, solve(input));
  }

  TEST(SmallTest, EveryRowSolution) {
    std::vector<std::string> input = {
      "11111",
      "11111",
      "11111",
      "11111"
    };

    std::vector<std::vector<int>> correct_solution = {{0}, {1}, {2}, {3}};
    EXPECT_EQ(correct_solution, solve(input));
  }

  TEST(SmallTest, EveryRowInSingleSolution) {
    std::vector<std::string> input = {
      "10000",
      "00100",
      "01000",
      "00001",
      "00010"
    };

    std::vector<std::vector<int>> correct_solution = {{0, 1, 2, 3, 4}};
    EXPECT_EQ(correct_solution, solve(input));
  }

}

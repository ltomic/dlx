#include "gtest/gtest.h"
#include "dlx.hpp"
#include "ExactCover.hpp"

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

    auto brute_sol = dlx::brute(input);
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
    EXPECT_EQ(correct_solution, dlx::brute(input));
  }

  TEST(TestBrute, NoSolution_1) {
    std::vector<std::string> input = { "0" };
    
    std::vector<std::vector<int>> correct_solution;
    EXPECT_EQ(correct_solution, dlx::brute(input));
  }

  TEST(TestBrute, EveryRowSolution) {
    std::vector<std::string> input = {
      "11111",
      "11111",
      "11111",
      "11111"
    };


    std::vector<std::vector<int>> correct_solution = {{0}, {1}, {2}, {3}};

    EXPECT_EQ(correct_solution, dlx::brute(input));
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
    EXPECT_EQ(correct_solution, dlx::brute(input));
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

    ExactCover cover(input);
    std::vector<std::vector<int>> sols = cover.solve();
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

    ExactCover cover(input);
    std::vector<std::vector<int>> correct_solution = {{0, 3, 6}};
    EXPECT_EQ(correct_solution, cover.solve());
  }

  TEST(SmallTest, NoSolution_1) {
    std::vector<std::string> input = { "0" };
    
    ExactCover cover(input);
    std::vector<std::vector<int>> correct_solution;
    EXPECT_EQ(correct_solution, cover.solve());
  }

  TEST(SmallTest, EveryRowSolution) {
    std::vector<std::string> input = {
      "11111",
      "11111",
      "11111",
      "11111"
    };

    ExactCover cover(input);
    std::vector<std::vector<int>> correct_solution = {{0}, {1}, {2}, {3}};
    EXPECT_EQ(correct_solution, cover.solve());
  }

  TEST(SmallTest, EveryRowInSingleSolution) {
    std::vector<std::string> input = {
      "10000",
      "00100",
      "01000",
      "00001",
      "00010"
    };

    ExactCover cover(input);
    std::vector<std::vector<int>> correct_solution = {{0, 1, 2, 3, 4}};
    EXPECT_EQ(correct_solution, cover.solve());
  }

}

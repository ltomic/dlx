#include "gtest/gtest.h"
#include "dlx.hpp"

#include <vector>
#include <string>

using std::vector;

namespace { 
  TEST(SmallTest, SingleSolution) {
    vector<std::string> input = {
      "1001001",
      "1001000",
      "0001101",
      "0010110",
      "0110011",
      "0100001"
    };

    vector<vector<vector<std::string>>> sols = solve(input);
    vector<vector<vector<std::string>>> correct = {
      {
        {"0", "3"}, {"1", "6"}, {"2", "4", "5"}
      }
    };
    EXPECT_EQ(sols, correct);
  }  

  TEST(SmallTest, SingleSolution_2) {
    vector<std::string> input = {
      "101010000",
      "100001100",
      "010100000",
      "010001010",
      "000010011",
      "000001011",
      "000100101"
    };

//    vector<vector<int>> correct_solution = {{0, 3, 6}};
    vector<vector<vector<std::string>>> correct_solution = {
      {
        {"0", "2", "4"}, {"1", "5", "7"}, {"3", "6", "8"}
      }
    };
    EXPECT_EQ(correct_solution, solve(input));
  }

  TEST(SmallTest, NoSolution_1) {
    vector<std::string> input = { "0" };
    
    vector<vector<vector<std::string>>> correct_solution;
    EXPECT_EQ(correct_solution, solve(input));
  }

  TEST(SmallTest, EveryRowSolution) {
    vector<std::string> input = {
      "11111",
      "11111",
      "11111",
      "11111"
    };

    //vector<vector<int>> correct_solution = {{0}, {1}, {2}, {3}};
    vector<vector<vector<std::string>>> correct_solution = {
      { {"0", "1", "2", "3", "4"} },
      { {"0", "1", "2", "3", "4"} },
      { {"0", "1", "2", "3", "4"} },
      { {"0", "1", "2", "3", "4"} }
    };
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

    //vector<vector<int>> correct_solution = {{0, 1, 2, 3, 4}};
    vector<vector<vector<std::string>>> correct_solution = {
      {
        {"0"}, {"1"}, {"2"}, {"3"}, {"4"}
      }
    };
    EXPECT_EQ(correct_solution, solve(input));
  }

}

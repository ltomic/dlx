#include "gtest/gtest.h"
#include "dlx.hpp"
#include "ExactCover.hpp"
#include "Node.hpp"
#include "ColumnHeader.hpp"

#include <vector>
#include <string>

namespace {
  TEST(MatrixConstruction, Simple1) {
    std::vector<std::string> input = {
      "1001001",
      "1001000",
      "0001101",
      "0010110",
      "0110011",
      "0100001"
    };

    ExactCover cover(input);
    
    std::vector<int> sizes;
    ColumnHeader* master = cover.get_master_header();
    for (ColumnHeader* i = (ColumnHeader*)master->get_right(); i != master; 
        i = (ColumnHeader*)i->get_right()) {
      sizes.push_back(i->get_size());
    }
    
    std::vector<int> correct_sizes = {2, 2, 2, 3, 2, 2, 4};
    //EXPECT_EQ(correct_sizes.size(), sizes.size());
    EXPECT_EQ(sizes, correct_sizes);
  }
}

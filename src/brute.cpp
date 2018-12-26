#include "brute.hpp"

#include <cassert>

std::vector<int> matrix_to_row_masks(const std::vector<std::string>& matrix) {
  std::vector<int> row_masks;

  for (std::string row: matrix) {
    int mask = 0;
    int len = row.size();
    for (int j = 0; j < len; ++j) {
      if (row[j] == '1') mask |= 1 << j;
    }
    row_masks.push_back(mask);
  }
  return row_masks;
}

const int BRUTE_ROW_COLUMN_LIMIT = 32;
std::vector<std::vector<int>> brute(const std::vector<std::string>& matrix) {
  int num_rows = matrix.size();
  int num_columns = matrix[0].size();
  assert(num_rows < BRUTE_ROW_COLUMN_LIMIT);
  assert(num_columns < BRUTE_ROW_COLUMN_LIMIT);

  int possibilites = (1 << num_rows);
  int all = (1 << num_columns) - 1;
  std::vector<int> row_masks = matrix_to_row_masks(matrix);

  std::vector<std::vector<int>> sols;
  for (int i = 0; i < possibilites; ++i) {
    int covered_columns = 0;
    bool flag = true;
    
    for (int j = 0; j < num_rows && flag; ++j) {
      if (((i >> j) & 1) == 0) continue;
      if (covered_columns & row_masks[j]) flag = false;
      covered_columns |= row_masks[j];
    }
    if (!flag || all != covered_columns) continue;
    
    std::vector<int> found_solution;
    for (int j = 0; j < num_rows; ++j) {
      if (((i >> j) & 1) == 0) continue;
      found_solution.push_back(j);
    }
    sols.push_back(found_solution);
  }
  return sols;
}

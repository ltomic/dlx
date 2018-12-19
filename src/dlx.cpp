#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdlib>

#include "util.hpp"
#include "dlx.hpp"
#include "ExactCover.hpp"

namespace dlx {
  ColumnHeader* find_smallest_column(Node *master) {
    ColumnHeader *smallest = NULL;

    for (ColumnHeader *i = (ColumnHeader*)master->get_right(); i != master; 
        i = (ColumnHeader*)i->get_right()) {
      if (smallest == NULL || smallest->get_size() > i->get_size())
        smallest = i;
    }
    return smallest;
  }

  std::vector<Node*> sol;
  void print_solution() {
    for (Node* i: sol) {

      std::cout << i->get_column_header()->get_name() << " ";
    }
    std::cout << std::endl;
  }

  void print_state(ColumnHeader* master) {
    for (ColumnHeader* i = (ColumnHeader*)master->get_down(); i != master; 
        i = (ColumnHeader*)i->get_down()) {
      printf("ROW %d:", i->get_name());
      for (Node* j = i->get_right(); j != i; j = j->get_right()) {
        printf("%d ", j->get_column_header()->get_name());
      }
      printf("\n");
    }
  }

  void search(ColumnHeader *master, std::function<void(const std::vector<int>&)> notify) {
    if (master->get_right() == master) {
      std::vector<int> names;
      for (auto i: sol) {
        while (i->get_column_header() != master) i = i->get_right();
        names.push_back(((ColumnHeader*)i)->get_name());
      }
      std::sort(names.begin(), names.end());
      notify(names);
      return;
    }
    
    ColumnHeader *column_to_cover = find_smallest_column(master); 
    
    column_to_cover->cover();
    //select a row from the latest covered column
    for (Node *row = column_to_cover->get_down(); row != column_to_cover; 
        row = row->get_down()) {
      sol.push_back(row);

      // remove all columns with 1s in the selected row
      for (Node *cell = row->get_right(); cell != row; cell = cell->get_right()) {
        if (cell->get_column_header() == master) continue;
        cell->get_column_header()->cover();
      }
      search(master, notify);
      
      sol.pop_back();

      // unselect current row - insert all column with 1s in the selected row
      for (Node *col = row->get_left(); col != row; col = col->get_left()) {
        col->get_column_header()->uncover();
      }
    }
  
    column_to_cover->uncover();
  }

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
};

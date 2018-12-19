#include "ExactCover.hpp"

#include <string>

#include "Node.hpp"
#include "ColumnHeader.hpp"
#include "dlx.hpp"
#include "util.hpp"

ExactCover::ExactCover(const std::vector<std::string>& matrix) {
  master_header = new ColumnHeader(-1); // TODO: mozda enum

  ColumnHeader *curr_column = master_header;
  // TODO: matrix empty
  // TODO: strings have to be equal lenghts
  size_t num_rows = matrix.size();
  for (size_t i = 0; i < num_rows; ++i) {
    master_header->push_up(new ColumnHeader(master_header, i));
  }
  
  size_t num_columns = matrix[0].size();
  for (size_t i = 0; i < num_columns; ++i) {
    curr_column->push_right(new ColumnHeader(i));
    curr_column = (ColumnHeader*)curr_column->get_right();
  }

  Node* row_header = master_header;
  for (std::string i: matrix) {
    curr_column = master_header;
    Node* last_in_row = row_header = row_header->get_down();
    
    for (char c: i) {
      curr_column = (ColumnHeader*)curr_column->get_right();
      if (c == '0') continue;
      
      Node* new_cell = new Node(curr_column);
      last_in_row->push_right(new_cell);
      last_in_row = new_cell;
      curr_column->push_up(new_cell);
    }
  }
}

std::vector<std::vector<int>> ExactCover::solve() {
  if (sols.size() > 0) return sols;
  dlx::search(master_header, 
      [this](const std::vector<int>& sol) {
        this->sols.push_back(sol); 
      });
  return sols;
}


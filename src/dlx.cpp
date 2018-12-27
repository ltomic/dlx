#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <string>

#include "util.hpp"
#include "dlx.hpp"

using std::vector;

class Node {
  public:
    Node(): Node("-1") {}
    Node(const std::string& name): Node(name, this) {}
    Node(const std::string& name, Node *head): name(name), head(head),
      left(this), right(this), down(this), up(this) {}

    void insert_down(Node* x) {
      down->up = x;
      x->down = down;
      x->up = this;
      down = x;
    }

    void insert_up(Node* x) {
      up->insert_down(x);
    }

    void insert_right(Node* x) {
      right->left = x;
      x->right = right;
      x->left = this;
      right = x;
    }

    void insert_left(Node* x) {
      left->insert_right(x);
    }

    size_t size;
    std::string name;
    Node *head;
    Node *left, *right, *down, *up;
};

Node* find_smallest_column(Node *master) {
  Node* smallest = NULL;

  for (Node *i = master->right; i != master; i = i->right) {
    if (smallest == NULL || smallest->size > i->size)
      smallest = i;
  }
  return smallest;
}

vector<Node*> sol;
void print_solution() {
  for (Node* i: sol) {
    std::cout << i->head->name << " ";
  }
  std::cout << std::endl;
}

void cover(Node* col) {
  col->right->left = col->left;
  col->left->right = col->right;

  for (Node* row = col->down; row != col; row = row->down) {
    for (Node* cell = row->right; cell != row; cell = cell->right) {
      cell->up->down = cell->down;
      cell->down->up = cell->up;
      cell->head->size--;
    }
  }
}

void uncover(Node* col) {
  for (Node* row = col->up; row != col; row = row->up) {
    for (Node* cell = row->left; cell != row; cell = cell->left) {
      cell->up->down = cell;
      cell->down->up = cell;
      cell->head->size++;
    }
  }
  col->right->left = col;
  col->left->right = col;
}

void search(Node *master, std::function<void(const vector<vector<std::string>>&)> notify) {
  if (master->right == master) {
    vector<vector<std::string>> names;
    std::transform(sol.begin(), sol.end(), std::back_inserter(names), 
        [master, &names](Node* x) -> vector<std::string> {
      vector<std::string> row_columns;
      row_columns.push_back(x->head->name);
      for (Node* i = x->right; i != x; i = i->right) {
        row_columns.push_back(i->head->name);
      }
      sort(row_columns.begin(), row_columns.end());
      return row_columns;
    });
    std::sort(names.begin(), names.end());
    notify(names);
    return;
  }
  
  Node* column_to_cover = find_smallest_column(master); 

  cover(column_to_cover);
  //column_to_cover->cover();
  //select a row from the latest covered column
  for (Node *row = column_to_cover->down; row != column_to_cover; row = row->down) {
    sol.push_back(row);

    // remove all columns with 1s in the selected row
    for (Node *cell = row->right; cell != row; cell = cell->right) {
      cover(cell->head);
    }
    search(master, notify);
    
    sol.pop_back();

    // unselect current row - insert all column with 1s in the selected row
    for (Node *cell = row->left; cell != row; cell = cell->left) {
      uncover(cell->head);
    }
  }

  uncover(column_to_cover);
//  column_to_cover->uncover();
}

vector<vector<vector<std::string>>> solve(const vector<std::string>& matrix) {
  Node* master = new Node("-1");

  Node* curr_column = master;
  // TODO: matrix empty
  // TODO: strings have to be equal lenghts
  size_t num_columns = matrix[0].size();
  for (size_t i = 0; i < num_columns; ++i) {
    master->insert_left(new Node(std::to_string(i)));
  }

  for (std::string i: matrix) {
    curr_column = master;
    Node* first_in_row = NULL;
    
    for (char c: i) {
      curr_column = curr_column->right;
      if (c == '0') continue;
      
      Node* new_cell = new Node("0", curr_column);
      if (first_in_row == NULL) first_in_row = new_cell;
      else first_in_row->insert_left(new_cell);
      
      curr_column->insert_up(new_cell);
      curr_column->size++;
    }
  }

  vector<vector<vector<std::string>>> sols;
  search(master, [&sols](const vector<vector<std::string>>& sol) mutable {
      sols.push_back(sol);
      });
  return sols;
}

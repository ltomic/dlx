#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdlib>

#include "util.hpp"
#include "dlx.hpp"

class Node {
  public:
    Node(): Node(-1, -1) {}
    Node(int type, int id): Node(type, id, this) {}
    Node(int type, int id, Node *head): type(type), id(id), head(head),
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
    // 0 - master node
    // 1 - column node
    // 2 - row node
    // 3 - cell node
    // Could recognize cell by what does it point to?
    int type;
    int id;
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

std::vector<Node*> sol;
void print_solution() {
  for (Node* i: sol) {
    std::cout << i->head->id << " ";
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

void print_state(Node* master) {
  for (Node* i = master->down; i != master; i = i->down) {
    printf("ROW %d:", i->id);
    for (Node* j = i->right; j != i; j = j->right) {
      printf("%d ", j->head->id);
    }
    printf("\n");
  }
}

void search(Node *master, std::function<void(const std::vector<int>&)> notify) {
  if (master->right == master) {
    std::vector<int> names;
    std::transform(sol.begin(), sol.end(), std::back_inserter(names), 
        [master](Node* x) -> int {
        while (x->head != master) x = x->right;
        return x->id;
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
      if (cell->head == master) continue;
      cover(cell->head);
    }
    search(master, notify);
    
    sol.pop_back();

    // unselect current row - insert all column with 1s in the selected row
    for (Node *cell = row->left; cell != row; cell = cell->left) {
      if (cell->head == master) continue;
      uncover(cell->head);
    }
  }

  uncover(column_to_cover);
//  column_to_cover->uncover();
}

std::vector<std::vector<int>> solve(const std::vector<std::string>& matrix) {
  Node* master = new Node(0, -1);

  Node* curr_column = master;
  // TODO: matrix empty
  // TODO: strings have to be equal lenghts
  size_t num_rows = matrix.size();
  for (size_t i = 0; i < num_rows; ++i) {
    master->insert_up(new Node(2, i, master));
  }
  
  size_t num_columns = matrix[0].size();
  for (size_t i = 0; i < num_columns; ++i) {
    curr_column->insert_right(new Node(1, i));
    curr_column = curr_column->right;
  }

  Node* row_header = master;
  for (std::string i: matrix) {
    curr_column = master;
    Node* last_in_row = row_header = row_header->down;
    
    for (char c: i) {
      curr_column = curr_column->right;
      if (c == '0') continue;
      
      Node* new_cell = new Node(3, 1, curr_column);
      last_in_row->insert_right(new_cell);
      last_in_row = new_cell;
      curr_column->insert_up(new_cell);
      curr_column->size++;
    }
  }

  std::vector<std::vector<int>> sols;
  search(master, [&sols](const std::vector<int>& sol) mutable {
      sols.push_back(sol);
      });

  return sols;
}

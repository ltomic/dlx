#include "Node.hpp"
#include "ColumnHeader.hpp"
#include <vector>
#include <iostream>

namespace dlx {

  ColumnHeader* findSmallestColumn(Node *h) {
    ColumnHeader *smallest = NULL;
    
    for (ColumnHeader *i = (ColumnHeader*)h->right(); i != h; i = (ColumnHeader*)i->right()) {
      if (smallest == NULL || smallest->getSize() > i->getSize())
        smallest = i;
    }

    return smallest;
  }

  std::vector<Node*> sol;
  void print_solution() {
    for (Node* i: sol) {
      std::cout << i->getColHeader()->getName() << " ";
    }
    std::cout << std::endl;
  }

  void search(Node *h) {
    if (h->right() == h) {
      print_solution();
      return;
    }

    ColumnHeader *colToCover = findSmallestColumn(h); 
    
    colToCover->cover();

    //select a row from the latest covered column
    for (Node *row = colToCover->down(); row != colToCover; row = row->down()) {
      sol.push_back(row);

      // remove all columns with 1s in the selected row
      for (Node *cell = row->right(); cell != row; cell = cell->right()) {
        cell->getColHeader()->cover();
      }
      search(h);
      
      sol.pop_back();

      // unselect current row - insert all column with 1s in the selected row
      for (Node *col = row->left(); col != row; col = col->left()) {
        col->getColHeader()->uncover();
      }
    }

    colToCover->uncover();
  }
};

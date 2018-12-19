#pragma once
#ifndef EXACTCOVER_HPP
#define EXACTCOVER_HPP

#include "Node.hpp"

#include <vector>
#include <string>

/**
 * Main purpose of this class is to convert various ways of representing exact cover
 * problem into a sparse matrix compatible for Dancing Links algorithm.
 **/
class ExactCover {
  public:
    ExactCover(const std::vector<std::string>& matrix);

    std::vector<std::vector<int>> solve();

    ColumnHeader* get_master_header() const {
      return master_header;
    }

  private:
    ColumnHeader* master_header;
    std::vector<std::vector<int>> sols;
};

#endif

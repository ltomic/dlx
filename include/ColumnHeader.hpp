#pragma once
#ifndef COLUMNHEADER_HPP
#define COLUMNHEADER_HPP

#include "Node.hpp"
#include <cstddef>

class ColumnHeader: public Node {
  public:
    void cover();
    void uncover();

    int getName();
    size_t getSize();

  private:
    int name;
    size_t sz;
    
    void decrease_size();
    void increase_size();
};

#endif

#pragma once
#ifndef COLUMNHEADER_HPP
#define COLUMNHEADER_HPP

#include "Node.hpp"
#include <cstddef>

class ColumnHeader: public Node {
  public:
    ColumnHeader();
    ColumnHeader(const int& name);
    ColumnHeader(ColumnHeader *header, const int& name);

    void cover();
    void uncover();

    int get_name();
    size_t get_size();
    
    void decrease_size();
    void increase_size();

  private:
    int name;
    size_t sz;
};

#endif

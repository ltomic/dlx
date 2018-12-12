#pragma once
#ifndef NODE_HPP
#define NODE_HPP

class ColumnHeader;

class Node {
  public:
    ColumnHeader* getColHeader() const;

    Node* left() const;
    Node* right() const;
    Node* up() const;
    Node* down() const;

    void setLeft(Node* x);
    void setRight(Node* x);
    void setUp(Node* x);
    void setDown(Node* x);

    void self_insert_horz();
    void self_insert_vert();
    void self_remove_horz();
    void self_remove_vert();
  
  private:
    Node *l, *r, *u, *d;
    ColumnHeader *colHeader;
};

#endif

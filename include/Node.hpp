#pragma once
#ifndef NODE_HPP
#define NODE_HPP

class ColumnHeader;

class Node {
  public:
    Node();
    Node(ColumnHeader* column);
    
    ColumnHeader* get_column_header() const;

    Node* get_left() const;
    Node* get_right() const;
    Node* get_up() const;
    Node* get_down() const;

    void set_left(Node* x);
    void set_right(Node* x);
    void set_up(Node* x);
    void set_down(Node* x);

    void reinsert_horizontal();
    void reinsert_vertical();
    void remove_horizontal();
    void remove_vertical();

    void push_right(Node* x);
    void push_left(Node* x);
    virtual void push_down(Node* x);
    virtual void push_up(Node* x);
  
  private:
    Node *left, *right, *up, *down;
    ColumnHeader *column_header;
};

#endif

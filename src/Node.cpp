#include "ColumnHeader.hpp"
#include "Node.hpp"

Node::Node(): Node(nullptr) {};
Node::Node(ColumnHeader* column): left(this), right(this), up(this), down(this), 
  column_header(column) {}

ColumnHeader* Node::get_column_header() const {
  return column_header;
}

Node* Node::get_left() const {
  return left;
}

Node* Node::get_right() const {
  return right;
}

Node* Node::get_up() const {
  return up;
}

Node* Node::get_down() const {
  return down;
}

void Node::set_left(Node* x) {
  left = x;
}

void Node::set_right(Node* x) {
  right = x;
}

void Node::set_up(Node* x) {
  up = x;
}

void Node::set_down(Node* x) {
  down = x;
}

// tijekom horizontalnog reinserta ne mijenjas svoj column
void Node::reinsert_horizontal() {
  right->set_left(this);
  left->set_right(this);
}

void Node::reinsert_vertical() {
  up->set_down(this);
  down->set_up(this);
  if (column_header != NULL)
    column_header->increase_size();
}

void Node::remove_horizontal() {
  right->set_left(this->get_left());
  left->set_right(this->get_right());
}

void Node::remove_vertical() {
  up->set_down(this->get_down());
  down->set_up(this->get_up());
  if (column_header != NULL)
    column_header->decrease_size();
}

void Node::push_right(Node* x) {
  right->set_left(x);
  x->set_right(this->get_right());
  x->set_left(this);
  this->set_right(x);
}

void Node::push_left(Node *x) {
  left->push_right(x);
}

void Node::push_down(Node *x) {
  down->set_up(x);
  x->set_down(this->get_down());
  x->set_up(this);
  this->set_down(x);
  if (column_header != NULL)
    column_header->increase_size();
}

void Node::push_up(Node *x) {
  up->push_down(x);
}

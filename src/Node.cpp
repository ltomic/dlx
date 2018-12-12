#include "Node.hpp"

ColumnHeader* Node::getColHeader() const {
  return colHeader;
}

Node* Node::left() const {
  return l;
}

Node* Node::right() const {
  return r;
}

Node* Node::up() const {
  return u;
}

Node* Node::down() const {
  return d;
}

void Node::setLeft(Node* x) {
  l = x;
}

void Node::setRight(Node* x) {
  r = x;
}

void Node::setUp(Node* x) {
  u = x;
}

void Node::setDown(Node* x) {
  d = x;
}

void Node::self_insert_horz() {
  this->right()->setLeft(this);
  this->left()->setRight(this);
}

void Node::self_insert_vert() {
  this->up()->setDown(this);
  this->down()->setUp(this);
}

void Node::self_remove_horz() {
  this->right()->setLeft(this->left());
  this->left()->setRight(this->right());
}

void Node::self_remove_vert() {
  this->up()->setDown(this->down());
  this->down()->setUp(this->up());
}


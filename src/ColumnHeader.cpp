#include "ColumnHeader.hpp"

void ColumnHeader::cover() {
	this->self_remove_horz();

	for (Node *row = this->down(); row != this; row = row->down()) {
		for (Node *cell = row->right(); cell != row; cell = cell->right()) {
			cell->self_remove_vert();
			cell->getColHeader()->decrease_size();
		}
	}
}

void ColumnHeader::uncover() {
	for (Node *row = this->up(); row != this; row = row->up()) {
		for (Node *cell = row->left(); cell != row; cell = cell->left()) {
			cell->self_insert_vert();
			cell->getColHeader()->increase_size();
		}
	}

	this->self_insert_horz();
}

int ColumnHeader::getName() {
  return name;
}

size_t ColumnHeader::getSize() {
  return size;
}

void ColumnHeader::decrease_size() {
	sz--;
}

void ColumnHeader::increase_size() {
	sz++;
}

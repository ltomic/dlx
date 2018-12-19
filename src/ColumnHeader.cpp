#include "ColumnHeader.hpp"

#include <cstdio>

ColumnHeader::ColumnHeader(): Node(this) {}

ColumnHeader::ColumnHeader(const int& name): Node(this), name(name) {}

ColumnHeader::ColumnHeader(ColumnHeader *header, const int& name): Node(header), name(name) {}

void ColumnHeader::cover() {
	this->remove_horizontal();

	for (Node *row = this->get_down(); row != this; row = row->get_down()) {
		for (Node *cell = row->get_right(); cell != row; cell = cell->get_right()) {
			cell->remove_vertical();
			cell->get_column_header()->decrease_size();
		}
	}
}

void ColumnHeader::uncover() {
	for (Node *row = this->get_up(); row != this; row = row->get_up()) {
		for (Node *cell = row->get_left(); cell != row; cell = cell->get_left()) {
			cell->reinsert_vertical();
			cell->get_column_header()->increase_size();
		}
	}

	this->reinsert_horizontal();
}

int ColumnHeader::get_name() {
  return name;
}

size_t ColumnHeader::get_size() {
  return sz;
}

void ColumnHeader::decrease_size() {
	sz--;
}

void ColumnHeader::increase_size() {
	sz++;
}

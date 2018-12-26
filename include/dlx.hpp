#pragma once
#ifndef DLX_HPP
#define DLX_HPP

#include <functional>

struct Node;

/**
 * Founds solutions of a exact cover problem given as a sparse matrix
 * whose rows and columns are doubly linked circular lists. When some
 * solution is found, function notify is called with list of rows ids(names)
 * that form a single solution
 **/
void search(Node *master, std::function<void(const std::vector<int>&)> notify);

/**
 * Simple, but inefficent way of finding solutions to exact cover problem given
 * as dense matrix of zeros and ones.
 * Used for testing.
 **/
std::vector<std::vector<int>> brute(const std::vector<std::string>& matrix);

std::vector<std::vector<int>> solve(const std::vector<std::string>& matrix);
#endif

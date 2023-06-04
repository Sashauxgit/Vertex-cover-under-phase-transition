#ifndef EXACTSOLVE_H
#define EXACTSOLVE_H

#include "..\graph\graph.h"
#include <vector>
#include <ctime>

#include "..\csvstream.h"

std::vector<int> branch_bound(Graph G, int current_vertex, std::vector<int> cover, int MAX_cover_size, int cover_edges_size, 
int MAX_edges_size, std::vector<bool> tags, size_t& tik, clock_t start, int hourBorder);

std::size_t combinations_count(int n, int k);
int exact_solution(const Graph &G);
bool exact_solution(const Graph &G, size_t &upstart, double &linCoeff, dataWriter &writer);

#endif
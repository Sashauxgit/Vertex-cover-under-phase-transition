#ifndef EXACTSOLVE2_H
#define EXACTSOLVE2_H

#include "..\graph\graph.h"
#include <vector>

std::vector<int> operator+(const std::vector<int>& v1, const std::vector<int>& v2);

int deg_lower_bound(const Graph &graph);

int exact_BandB_solution(Graph G, int upper_bound, std::vector<int> partial_coverage, long long H);

#endif
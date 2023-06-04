#ifndef HEURISTICSOLVES_H
#define HEURISTICSOLVES_H

#include "..\graph\graph.h"
#include <vector>

int lazy_algorithm(Graph graph);
int greedy_algorithm(Graph graph);
int linear_algorithm(Graph graph);

std::vector<int> partical_branch_bound(Graph G, int current_vertex, std::vector<int> cover, int MAX_cover_size, int cover_edges_size, 
int MAX_edges_size, std::vector<bool> tags, std::size_t& tik, double& linear_coeff);
int developed_algorithm(Graph graph);

#endif
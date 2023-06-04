#include "graph/graph.h"
#include "solves/heuristic_solves.h"
#include "solves/exact_solve.h"
#include "solves/exact_solve_2.h"
#include "csvstream.h"

#include <iostream>
#include <ctime>

using namespace std;

int main() {
    Graph graph = Graph(4, 4);
    linear_algorithm(graph);
    return 0;
}
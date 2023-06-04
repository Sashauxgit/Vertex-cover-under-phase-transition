
#include "exact_solve_2.h"
#include <iostream>

std::vector<int> operator+(const std::vector<int>& v1, const std::vector<int>& v2){
    std::vector<int> v = std::vector<int>(v1.size() + v2.size());
    for (int i = 0; i < v1.size(); i++) v[i] = v1[i];
    for (int j = 0; j < v2.size(); j++) v[v1.size() + j] = v2[j];
    return v;
}

int deg_lower_bound(const Graph &graph) {
    Graph modified_G = graph;
    int degSum = 0;
    int i;
    for (i = 0; degSum < graph.getEdgeCount(); i++) {
        int newV_i = modified_G.getHighDegreeV();
        modified_G.deleteIncidenceEdges(newV_i);
        degSum += graph.getValency(newV_i);
    }

    //if (modified_G.getEdgeCount() != 0 && modified_G.getHighDegreeV() == 0) modified_G.printGraph();

    if (modified_G.getEdgeCount() == 0) return i;
    else return (int)(i + modified_G.getEdgeCount() / modified_G.getValency(modified_G.getHighDegreeV()));
}

int exact_BandB_solution(Graph G, int upper_bound, std::vector<int> partial_coverage, long long H){
    //std::cout << H << '\n';
    if ((partial_coverage.size() + deg_lower_bound(G)) >= upper_bound) return upper_bound;

    if (G) {
        int currentVertex = G.getHighDegreeV();
        std::vector<int> V_neighborhood = G.getAdjacentVertices(currentVertex);
        int PC_1 = exact_BandB_solution(graphDestroy(G, V_neighborhood, currentVertex), upper_bound, partial_coverage + V_neighborhood, H + 1);
        partial_coverage.push_back(currentVertex);
        int PC_2 = exact_BandB_solution(std::move(G) - currentVertex, std::min(upper_bound, PC_1), std::move(partial_coverage), H + 1);
        return std::min(PC_1, PC_2);
    } else return partial_coverage.size();
}
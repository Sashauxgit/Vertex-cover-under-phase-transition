#include "heuristic_solves.h"
#include "simplex.h"

using namespace std;

int lazy_algorithm(Graph G){ // Ленивый алгоритм
    vector<int> result;
    int result_size = 0;

    while (G.getEdgeCount() > 0) {
        result.push_back(G.getEndpoints(0).v1);
        result.push_back(G.getEndpoints(0).v2);
        result_size += 2;
        
        G.deleteIncidenceEdges(G.getEndpoints(0).v1);
        G.deleteIncidenceEdges(G.getEndpoints(0).v2);
    }

    return result_size;
}

int greedy_algorithm(Graph G) { // Жадный алгоритм
    vector<int> result;
    int result_size = 0;

    while (G.getEdgeCount() > 0) {
        int current_vertex = G.getHighDegreeV();
        G.deleteIncidenceEdges(current_vertex);
        result.push_back(current_vertex);
        result_size++;
    }

    return result_size;
}

int linear_algorithm(Graph G) { // Линейный алгоритм
    int colSizeA = G.getVertexCount();  //should initialise columns size in A
    int rowSizeA = G.getEdgeCount();  //should initialise columns row in A[][] vector


    std::vector <std::vector<float> > A(rowSizeA, std::vector<float>(colSizeA, 0));

    std::vector<float> B(rowSizeA, -1);
    std::vector<float> C(colSizeA, 1);

    for(int i=0;i<rowSizeA;i++){         //make a vector from given array
        for(int j=0; j<colSizeA;j++){
            A[i][j] = - (float)G.getIncidenceMatrix()[i][j];
        }
    }

    Simplex simplex(A,B,C);
    simplex.CalculateSimplex();
}

int developed_algorithm(Graph G) { // Новый разработанный эвристический алгоритм
    vector<bool> tags = vector<bool>(G.getVertexCount());
    for (vector<bool>::iterator iter = tags.begin(); iter != tags.end(); iter++) *iter = true;
    
    size_t prevTik = 0;
    double linCoeff = 0;

    for (int N = G.getVertexCount() - 1; N > 0; N--) {
        size_t tik = -prevTik;
        vector<int> cover = partical_branch_bound(G, G.getHighDegreeV(), vector<int>(), N, 0, G.getEdgeCount(), tags, tik, linCoeff);
        if (cover.size() == 0 || cover[0] == -1) return N + 1;
        
        if (N == G.getVertexCount() - 1) linCoeff = (double)tik;
        else linCoeff = ((double)tik + linCoeff) / 2;
        prevTik = tik + prevTik;
    }
    return 1;
}

std::vector<int> partical_branch_bound(Graph G, int current_vertex, std::vector<int> cover, int MAX_cover_size, int cover_edges_size, 
int MAX_edges_size, std::vector<bool> tags, size_t& tik, double& linear_coeff) {
    tags[current_vertex] = false;
    tik++;

    if (linear_coeff != 0 && (double)tik / linear_coeff > 786*G.getVertexCount()) return vector<int>({-1});

    if (cover_edges_size == MAX_edges_size) return cover;
    if (cover.size() == MAX_cover_size) return vector<int>();
    
    int next_vertex = G.getHighDegreeV(tags);
    if (next_vertex == -1) return vector<int>();
    
    cover.push_back(current_vertex);
    vector<int> solve = partical_branch_bound(G - current_vertex, current_vertex < next_vertex ? next_vertex - 1 : next_vertex, 
cover, MAX_cover_size, cover_edges_size + G.getValency(current_vertex), MAX_edges_size, [=](int v) {
        vector<bool> newTags = tags;
        newTags.erase(newTags.begin() + v);
        return newTags;
    }(current_vertex), tik, linear_coeff);
    if (solve.size() > 0) return solve;
    
    cover.pop_back();
    solve = partical_branch_bound(G, next_vertex, cover, MAX_cover_size, cover_edges_size, MAX_edges_size, tags, tik, linear_coeff);

    return solve;
}
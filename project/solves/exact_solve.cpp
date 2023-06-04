#include "exact_solve.h"

#include <iostream>
#include <algorithm>

using namespace std;

vector<int> branch_bound(Graph G, int current_vertex, vector<int> cover, int MAX_cover_size, int cover_edges_size, 
int MAX_edges_size, vector<bool> tags, size_t& tik, clock_t start, int hourBorder) {

    if ((clock() - start) / (CLOCKS_PER_SEC * 1200) > hourBorder) return vector<int>({-1});

    tags[current_vertex] = false;
    tik++;

    if (cover_edges_size == MAX_edges_size) return cover;
    if (cover.size() == MAX_cover_size) return vector<int>();
    
    int next_vertex = G.getHighDegreeV(tags);
    if (next_vertex == -1) return vector<int>();
    
    cover.push_back(current_vertex);
    vector<int> solve = branch_bound(G - current_vertex, current_vertex < next_vertex ? next_vertex - 1 : next_vertex, 
cover, MAX_cover_size, cover_edges_size + G.getValency(current_vertex), MAX_edges_size, [=](int v) {
        vector<bool> newTags = tags;
        newTags.erase(newTags.begin() + v);
        return newTags;
    }(current_vertex), tik, start, hourBorder);
    if (solve.size() > 0) return solve;
    
    cover.pop_back();
    solve = branch_bound(G, next_vertex, cover, MAX_cover_size, cover_edges_size, MAX_edges_size, tags, tik, start, hourBorder);

    return solve;
}

int exact_solution(const Graph &G) {
    vector<bool> tags = vector<bool>(G.getVertexCount());
    for (vector<bool>::iterator iter = tags.begin(); iter != tags.end(); iter++) *iter = true;
    for (int N = G.getVertexCount() - 1; N > 0; N--) {
        size_t tik = 0;
        int cover_size = branch_bound(G, G.getHighDegreeV(), vector<int>(), N, 0, G.getEdgeCount(), tags, tik, clock(), 3).size();
        if (cover_size < N) {
            if (cover_size > 0) N = cover_size;
            else return N + 1;
        }
    }

    return 1;
}

bool exact_solution(const Graph &G, size_t &upstart, double &linCoeff, dataWriter &writer) {
    vector<bool> tags = vector<bool>(G.getVertexCount());
    for (vector<bool>::iterator iter = tags.begin(); iter != tags.end(); iter++) *iter = true;
    size_t prevTik = 0;
    double sumDiffTik = 0;
    for (int N = G.getVertexCount() - 1; N > 0; N--) {
        size_t tik = 0;
        vector<int> cover = branch_bound(G, G.getHighDegreeV(), vector<int>(), N, 0, G.getEdgeCount(), tags, tik, clock(), 3);

        upstart = tik - prevTik;
        if (N != G.getVertexCount() - 1) {
            linCoeff = sumDiffTik / (G.getVertexCount() - N - 1);
            writer << N << linCoeff << dataWriter::endentry;
        }

        if (cover.size() == 0) return true;
        if (cover[0] == -1) return false;

        sumDiffTik += (double)tik - prevTik;
        prevTik = tik;
    }
    return false;
}


size_t combinations_count(int n, int k) {
    if (k == 0 || k == n) return (size_t)1;
    else return combinations_count(n - 1, k) + combinations_count(n - 1, k - 1);
}
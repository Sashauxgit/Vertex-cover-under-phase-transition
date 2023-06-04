#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct AdjacentVertices {
public:
    int v1;
    int v2;
};

class Graph {
protected:
    std::vector<std::vector<int>> incidence_matrix;
    std::vector<int> valencies;
    int vertex_count = 0;
    int edges_count = 0;
        
public:
    Graph() = default;
    ~Graph();
    Graph(int k_vertex, int k_edges, std::vector<AdjacentVertices> possible_edges = std::vector<AdjacentVertices>());
    Graph(const Graph& obj);
    Graph(Graph&& obj);
    Graph& operator = (const Graph& obj);
    Graph& operator = (Graph&& obj);
    int getVertexCount() const;
    int getEdgeCount() const;
    int getValency(int v) const;
    int getHighDegreeV() const;
    int getHighDegreeV(std::vector<bool> tags) const;
    AdjacentVertices getEndpoints(int e) const;
    std::vector<int> getIncidenceEdges(int v) const;
    std::vector<int> getAdjacentVertices(int v) const;
    bool isAdjacent(int v1, int v2) const;
    void deleteEdge(int e);
    void deleteIncidenceEdges(int v);
    operator bool() const;
    friend Graph operator-(Graph graph, int vertex);
    //friend Graph operator-(Graph graph, const std::vector<int> &vertexes);
    friend Graph graphDestroy(Graph graph, const std::vector<int> &vertexes, int mainVertex);
    void printGraph() const;        
};

Graph operator-(Graph graph, int vertex);
//Graph operator-(Graph graph, const std::vector<int> &vertexes);
Graph graphDestroy(Graph graph, const std::vector<int> &vertexes, int mainVertex);

class FullGraph: public Graph {
public:
    FullGraph() = default;
    FullGraph(int k_vertex);
    FullGraph(const FullGraph& obj);
    FullGraph(FullGraph&& obj);
    FullGraph& operator = (const FullGraph& obj);
    FullGraph& operator = (FullGraph&& obj);
};

class BipartGraph: public Graph {
protected:
    int left_vertex_count = 0;
    int right_vertex_count = 0;
public:
    BipartGraph() = default;
    BipartGraph(int k_left_vertex, int k_right_vertex, int k_edges);
    BipartGraph(const BipartGraph& obj);
    BipartGraph(BipartGraph&& obj);
    BipartGraph& operator = (const BipartGraph& obj);
    BipartGraph& operator = (BipartGraph&& obj);
};

#endif
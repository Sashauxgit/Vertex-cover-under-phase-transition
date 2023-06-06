#include "graph.h"

#include <iostream>
#include <vector>
#include <ctime>

//#define INC_M
#define SME_M

using namespace std;

Graph::Graph(int k_vertex, int k_edges, vector<AdjacentVertices> possible_edges) {
    vertex_count = k_vertex;
    edges_count = k_edges;

    if (possible_edges.size() == 0)
        for (int i = 0; i < k_vertex - 1; i++)
            for (int j = i + 1; j < k_vertex; j++)
                possible_edges.push_back({i, j});
    
    incidence_matrix = vector<vector<int>>(edges_count);

    valencies = vector<int>(vertex_count);
    for (int j = 0; j < vertex_count; j++) valencies[j] = 0;

    srand(time(NULL));

    for (int i = 0; i < edges_count; i++) {
        incidence_matrix[i] = vector<int>(vertex_count);
        for (int j = 0; j < vertex_count; j++) incidence_matrix[i][j] = 0;

        int random_edge_index = (int)((long double)rand() / (long double)RAND_MAX * (long double)(possible_edges.size() - 1));

        incidence_matrix[i][possible_edges[random_edge_index].v1] = 1;
        incidence_matrix[i][possible_edges[random_edge_index].v2] = 1;

        valencies[possible_edges.at(random_edge_index).v1]++;
        valencies[possible_edges.at(random_edge_index).v2]++;

        possible_edges.erase(possible_edges.begin() + random_edge_index);
    }
}

FullGraph::FullGraph(int k_vertex){
    valencies = vector<int>(k_vertex);
    for (int k = 0; k < k_vertex; k++) valencies[k] = 0;
    
    for (int i = 0; i < k_vertex - 1; i++)
        for (int j = i + 1; j < k_vertex; j++) {
            incidence_matrix.push_back(vector<int>(k_vertex));
            for (int k = 0; k < k_vertex; k++) incidence_matrix.back()[k] = 0;
            
            incidence_matrix.back()[i] = 1;
            incidence_matrix.back()[j] = 1;

            valencies[i]++;
            valencies[j]++;
        }

    vertex_count = k_vertex;
    edges_count = incidence_matrix.size();
}

BipartGraph::BipartGraph(int k_left_vertex, int k_right_vertex, int k_edges)
    :Graph(k_left_vertex + k_right_vertex, k_edges, [](int k_left_vertex, int k_right_vertex){
        vector<AdjacentVertices> possible_edges;
        for (int i = 0; i < k_left_vertex; i++)
            for (int j = k_left_vertex; j < k_left_vertex + k_right_vertex; j++)
                possible_edges.push_back({i, j});
        return possible_edges;
    }(k_left_vertex, k_right_vertex)),
    left_vertex_count(k_left_vertex), right_vertex_count(k_right_vertex){}

/*
Graph::~Graph(){
    cout << "Destructor!\n"; //
    delete valencies;
    for (int i = 0; i < incidence_matrix.size(); i++)
        delete incidence_matrix[i];
}
*/

Graph::Graph(const Graph& obj){
    //cout << "copy-constructor\n"; //

    this->vertex_count = obj.vertex_count;
    this->edges_count = obj.edges_count;

    this->incidence_matrix = vector<vector<int>>(this->edges_count);
    for (int i = 0; i < this->edges_count; i++) {
        this->incidence_matrix[i] = vector<int>(this->vertex_count);
        for (int j = 0; j < this->vertex_count; j++) 
            this->incidence_matrix[i][j] = obj.incidence_matrix[i][j];
    }
    this->valencies = vector<int>(this->vertex_count);
    for (int k = 0; k < this->vertex_count; k++) 
        this->valencies[k] = obj.valencies[k];
}

Graph::Graph(Graph&& obj){
    //cout << "move-constructor\n"; //

    swap(this->vertex_count, obj.vertex_count);
    swap(this->edges_count, obj.edges_count);
    swap(this->incidence_matrix, obj.incidence_matrix);
    swap(this->valencies, obj.valencies);
}

Graph& Graph::operator = (const Graph& obj){
    //cout << "copy-operator\n"; //
    if (&obj == this) return *this;

    //this->~Graph();

    this->vertex_count = obj.vertex_count;
    this->edges_count = obj.edges_count;

    this->incidence_matrix = vector<vector<int>>(this->edges_count);
    for (int i = 0; i < this->edges_count; i++) {
        this->incidence_matrix[i] = vector<int>(this->vertex_count);
        for (int j = 0; j < this->vertex_count; j++) 
            this->incidence_matrix[i][j] = obj.incidence_matrix[i][j];
    }
    this->valencies = vector<int>(this->vertex_count);
    for (int k = 0; k < this->vertex_count; k++) 
        this->valencies[k] = obj.valencies[k];
    
    return *this;
}

Graph& Graph::operator = (Graph&& obj){
    //cout << "move-operator\n"; //
    if (&obj == this) return *this;

    swap(this->vertex_count, obj.vertex_count);
    swap(this->edges_count, obj.edges_count);
    swap(this->incidence_matrix, obj.incidence_matrix);
    swap(this->valencies, obj.valencies);

    return *this;
}

FullGraph::FullGraph(const FullGraph& obj):Graph::Graph(obj){}
FullGraph::FullGraph(FullGraph&& obj):Graph::Graph(move(obj)){}

FullGraph& FullGraph::operator = (const FullGraph& obj){
    Graph::operator=(obj);
    return *this;
}
FullGraph& FullGraph::operator = (FullGraph&& obj){
    Graph::operator=(move(obj));
    return *this;
}

BipartGraph::BipartGraph(const BipartGraph& obj):Graph::Graph(obj){
    this->left_vertex_count = obj.left_vertex_count;
    this->right_vertex_count = obj.right_vertex_count;
}

BipartGraph::BipartGraph(BipartGraph&& obj):Graph::Graph(move(obj)){
    swap(this->left_vertex_count, obj.left_vertex_count);
    swap(this->right_vertex_count, obj.right_vertex_count);
}

BipartGraph& BipartGraph::operator = (const BipartGraph& obj){
    Graph::operator=(obj);
    this->left_vertex_count = obj.left_vertex_count;
    this->right_vertex_count = obj.right_vertex_count;
    return *this;
}

BipartGraph& BipartGraph::operator = (BipartGraph&& obj){
    Graph::operator=(move(obj));
    swap(this->left_vertex_count, obj.left_vertex_count);
    swap(this->right_vertex_count, obj.right_vertex_count);
    return *this;
}

int Graph::getVertexCount() const{
    return vertex_count;
}

int Graph::getEdgeCount() const{
    return edges_count;
}

int Graph::getValency(int v) const{
    return valencies[v];
}

vector<int> Graph::getIncidenceEdges(int v) const{
    vector<int> incidence_list = vector<int>(valencies[v]);
    for (int i = 0, k = 0; i < edges_count && k < valencies[v]; i++)
        if (incidence_matrix[i][v]){
            incidence_list[k] = i;
            k++;
        }
    return incidence_list;
}

vector<int> Graph::getAdjacentVertices(int v) const{
    vector<int> incidenceList = getIncidenceEdges(v);
    for (int i = 0; i < valencies[v]; i++) {
        AdjacentVertices v_v = getEndpoints(incidenceList.at(i));
        if (v_v.v1 != v) incidenceList.at(i) = v_v.v1;
        else incidenceList.at(i) = v_v.v2;
    }
    return incidenceList;
}

AdjacentVertices Graph::getEndpoints(int e) const{
    AdjacentVertices incidenceVertices;
    for (int j = 0, k = 0; j < vertex_count && k < 2; j++)
        if (incidence_matrix[e][j]) {
            switch (k) {
                case 0: 
                    incidenceVertices.v1 = j;
                    break;
                case 1: 
                    incidenceVertices.v2 = j;
                    break;
            }
            k++;
        }
    return incidenceVertices;
}

void Graph::deleteEdge(int e){
    AdjacentVertices incidenceVertices = getEndpoints(e);
    valencies[incidenceVertices.v1]--;
    valencies[incidenceVertices.v2]--;
    //std::cout << "2\n";
    incidence_matrix.erase(incidence_matrix.begin() + e);
    edges_count--;
}

bool Graph::isAdjacent(int v1, int v2) const{
    vector<int> adjacentList = getAdjacentVertices(v1);
    for (int i = 0; i < valencies[v1]; i++) if (adjacentList.at(i) == v2) return true;
    return false;
}

void Graph::printGraph() const{
    if (vertex_count == 0) {
        cout << "Empty graph\n";
        return;
    }

#ifdef INC_M
    cout << "Incidence matrix:\n";
    for (int i = 0; i < edges_count; i++) {
        cout << "|";
        for (int j = 0; j < vertex_count; j++) cout << this->incidence_matrix[i][j] << "";
        cout << "|\n";
    }
    cout << "\n";
#endif

#ifdef SME_M
    cout << "Adjacency lists:\n";
    for (int j = 0; j < vertex_count; j++) {
        cout << j + 1 << ": [";

        vector<int> adjacentList = getAdjacentVertices(j);
        for (int i = 0; i < valencies[j]; i++) cout << adjacentList.at(i) + 1 << ",\t";

        cout << "];\n";
    }
#endif
}

void Graph::deleteIncidenceEdges(int v){
    const vector<int> incidenceEdges = getIncidenceEdges(v);
    for (int i = incidenceEdges.size() - 1; i >= 0; i--) deleteEdge(incidenceEdges.at(i));
}

Graph operator-(Graph graph, int vertex){
    //Graph graph_0 = graph;
    graph.deleteIncidenceEdges(vertex);
    for (int i = 0; i < graph.edges_count; i++) {

        //int s = 0;//
        //for (int j = 0; j < graph.vertex_count; j++) if (graph.incidence_matrix[i][j] == 1) s++; //
        //cout << "1: s = " << s << "\n"; //

        graph.incidence_matrix[i].erase(graph.incidence_matrix[i].begin() + vertex);

        //s = 0;//
        //for (int j = 0; j < graph.vertex_count - 1; j++) if (graph.incidence_matrix[i][j] == 1) s++; //
        //cout << "2: s = " << s << "\n"; //
        //if (s < 2) { //
        //    cout << graph_0.getVertexCount();
        //    cout << "\nv = " << vertex << '\n';
        //    abort(); //
        //}
    }

    graph.valencies.erase(graph.valencies.begin() + vertex);
    graph.vertex_count--;

    return graph;
}
/*
Graph operator-(Graph graph, const vector<int> &vertexes){
    //vector<int>::iterator iter = vertexes.begin(); iter != vertexes.end(); iter++
    for (int k = 0; k < vertexes.size(); k++) graph.deleteIncidenceEdges(vertexes[k]);

    for (int i = 0; i < graph.edges_count; i++) {
        for (int k = 0; k < vertexes.size(); k++) graph.incidence_matrix[i][vertexes[k]] = -1;
        
        vector<int>::iterator iter = graph.incidence_matrix[i].begin();
        for (int j = 0; j < graph.vertex_count; j++) {
            if (graph.incidence_matrix[i][j] != -1) {
                *iter = graph.incidence_matrix[i][j];
                iter++;
            }
        }
    }

    for (int k = 0; k < vertexes.size(); k++) graph.valencies[vertexes[k]] = -1;
        
    vector<int>::iterator iter = graph.valencies.begin();
    for (int j = 0; j < graph.vertex_count; j++) {
        if (graph.valencies[j] != -1) {
            *iter = graph.valencies[j];
            iter++;
        }
    }

    graph.vertex_count -= vertexes.size();

    return graph;
}
8*/
Graph graphDestroy(Graph graph, const std::vector<int> &vertexes, int mainVertex) {
    graph.deleteIncidenceEdges(mainVertex);
    for (int k = 0; k < vertexes.size(); k++) graph.deleteIncidenceEdges(vertexes[k]);

    for (int i = 0; i < graph.edges_count; i++) {
        graph.incidence_matrix[i][mainVertex] = -1;
        for (int k = 0; k < vertexes.size(); k++) graph.incidence_matrix[i][vertexes[k]] = -1;
        
        vector<int>::iterator iter = graph.incidence_matrix[i].begin();
        for (int j = 0; j < graph.vertex_count; j++) {
            if (graph.incidence_matrix[i][j] != -1) {
                *iter = graph.incidence_matrix[i][j];
                iter++;
            }
        }
    }

    graph.valencies[mainVertex] = -1;
    for (int k = 0; k < vertexes.size(); k++) graph.valencies[vertexes[k]] = -1;
        
    vector<int>::iterator iter = graph.valencies.begin();
    for (int j = 0; j < graph.vertex_count; j++) {
        if (graph.valencies[j] != -1) {
            *iter = graph.valencies[j];
            iter++;
        }
    }

    graph.vertex_count = graph.vertex_count - vertexes.size() - 1;

    return graph;
}

int Graph::getHighDegreeV() const {
    int max_degree = 0;
    int max_vertex;
    
    for (int i = 0; i < vertex_count; i++) 
        if (valencies[i] >= max_degree) {
            max_degree = valencies[i];
            max_vertex = i;
        }

    return max_vertex;
}

int Graph::getHighDegreeV(vector<bool> tags) const {
    int max_degree = 0;
    int max_vertex = -1;
    
    for (int i = 0; i < vertex_count; i++) 
        if (valencies[i] >= max_degree && tags[i]) {
            max_degree = valencies[i];
            max_vertex = i;
        }

    return max_vertex;
}

Graph::operator bool() const {
    return (bool)vertex_count;
}


Graph::~Graph(){
    for (vector<vector<int>>::iterator iter = incidence_matrix.begin(); iter != incidence_matrix.end(); iter++) {
        (*iter).clear();
    }
    incidence_matrix.clear();
}

std::vector<std::vector<int>> Graph::getIncidenceMatrix() {
    return this->incidence_matrix;
}
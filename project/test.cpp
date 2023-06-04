#include "graph\graph.h"
#include "solves\exact_solve_2.h"

#include <iostream>
#include <vector>
#include <set>

using namespace std;

void f(long long n) {
    cout << n << '\n';
    if (n > 0) f((long long)(n - 1));
}

int main(int argc, char **argv) {
    int V = atoi(argv[1]);
    if (argc == 2) {
        FullGraph graph = FullGraph(V);
        cout << exact_BandB_solution((Graph)graph, V, vector<int>(), 0);
    }
    if (argc == 3) {
        int E = atoi(argv[2]);
        Graph graph = Graph(V, E);
        cout << exact_BandB_solution(graph, V, vector<int>(), 0);
    }
    //graph.printGraph();
    //std::cout << "!!!\n";

    //f(1000000000000);
    //cout << "!!!";

    
 /*
    BipartGraph graph1 = BipartGraph(3, 5, 4);
    //BipartGraph graph2 = BipartGraph(3, 3, 9);
    graph1.printGraph();
    cout << graph1.getVertexCount() << "\n";
    cout << graph1.getEdgeCount() << "\n";
    cout << graph1.left_vertex_count << "\n";
    cout << graph1.right_vertex_count << "\n";
    //graph2.printGraph();
    //FullGraph graph2 = move(graph1);
    //BipartGraph graph2 = move(graph1);
    //graph1.deleteEdge(0);
    //graph1.printGraph();
    //graph2.printGraph();

    Graph graph = (Graph)graph1;
    graph.printGraph();
    cout << graph.getVertexCount() << "\n";
    cout << graph.getEdgeCount() << "\n";
    //cout << graph.left_vertex_count << "\n";
    //cout << graph.right_vertex_count << "\n";
    */
    return 0;
}
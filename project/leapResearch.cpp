#include "graph\graph.h"
#include "solves\exact_solve.h"
#include "csvstream.h"

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    dataWriter fullWriter("tikResearch\\full.csv");
    
    fullWriter << "K\\c";
    for (float c = 0.1; c < 1; c += 0.1) fullWriter << c;

    for (int N = 15; N <= 40; N += 5) {
        cout << "N = " << N << ": c(";

        fullWriter << dataWriter::endentry << N;

        for (float c = 0.1; c < 1; c += 0.1) {
            cout << c << ", ";
            
            Graph graph = Graph(N, (int)(c * N * (N - 1) / 2));

            dataWriter writer("tikResearch\\tik_datas-(N_" + to_string(N) + ", c_" + to_string(c) + ").csv");
            writer << "K" << "mean coeff of linearity" << dataWriter::endentry;
            
            size_t upstart;
            double linCoeff;
            bool success = exact_solution(graph, upstart, linCoeff, writer);
            
            fullWriter << (double)upstart / linCoeff;
            
            if (success) writer << "success" << " +" << dataWriter::endentry;
            else writer << "success" << " -"<< dataWriter::endentry;
            
        }
        cout << ")\n";
    }

    return 0;
}
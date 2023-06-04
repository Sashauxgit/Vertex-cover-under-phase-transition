#include "graph\graph.h"
#include "solves\exact_solve.h"
#include "csvstream.h"

#include <iostream>
#include <vector>
#include <string>

#include <ctime>

using namespace std;

int main(int argc, char **argv) {
    for (int N = 15; N <= 40; N += 5) {
        cout << "______________________________\n";
        cout << "|N = " << N << "|\n______________________________\n";
        
        vector<int> C;
        for (int i = 1; i <= 5; i++) {
            C.push_back(i);
        }
        for (int i = 10; i < N; i += 5) {
            C.push_back(i);
        }

        for (int i = 0; i < 5 + (N - 10) / 5; i++) {
            cout << "C: " << i + 1 << "/" << 5 + (N - 10) / 5 << " - K(";

            dataWriter writer("datas\\C_" + to_string(C[i]) + "\\result_datas-(N_" + to_string(N) + ").csv");
            writer << "K_cover" << "solving time" << dataWriter::endentry;

            dataWriter shareWriter("shareDatas\\C_" + to_string(C[i]) + "\\result_datas-(N_" + to_string(N) + ").csv");
            shareWriter << "share of cover" << "solving time" << dataWriter::endentry;
            
            string nameShares[10] = {" 0-0.1", " 0.1-0.2", " 0.2-0.3", " 0.3-0.4", " 0.4-0.5", " 0.5-0.6", " 0.6-0.7", " 0.7-0.8", " 0.8-0.9", " 0.9-1"};
            double shareTimes[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int shareCounts[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

            for (int K = N - 1; K > 0; K--) {
                Graph graph = Graph(N, (C[i]) * (N - 1) / 2);
                vector<bool> tags = vector<bool>(graph.getVertexCount());
                for (vector<bool>::iterator iter = tags.begin(); iter != tags.end(); iter++) *iter = true;

                size_t tik = 0;
                
                clock_t start = clock();
                branch_bound(graph, graph.getHighDegreeV(), vector<int>(), K, 0, graph.getEdgeCount(), tags, tik, start, 240).size();
                clock_t end = clock();
                
                writer << K << ((double)(end - start))/CLOCKS_PER_SEC << dataWriter::endentry;
                shareTimes[(int)(((double)K / N) * 10)] += ((double)(end - start))/CLOCKS_PER_SEC;
                shareCounts[(int)(((double)K / N) * 10)]++;

                cout << K << ", ";
            }
            
            for (int i = 0; i < 10; i++) shareWriter << nameShares[i] << shareTimes[i] / shareCounts[i] << dataWriter::endentry;

            cout << ")\n";
        }
    }

    cout << "______________________________\n";
    return 0;
}